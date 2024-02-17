#include <stdlib.h>
#include <stdio.h>

#include <raylib.h>

#include "state.h"
#include "gameInformations.h"
#include "GridTileDef.h"

#include "drawMenuElement.h"

#include "getDimensions.h"
#include "ProvinceTextures.h"
#include "createCamera.h"
#include "GetPoliticalDivision.h"
#include "ShowPlayer.h"
#include "GetProvinceInformation.h"

union layers {
    struct layersS {
        unsigned char provinceInfo : 1;
        unsigned char countryInfo : 1;
    } indivLayers;
    unsigned char layers;
};

void play(enum state* state) {
    extern struct gameInformations info;

    union layers topLayer = { 0 };

    int width = 0;
    int height = 0;
    int radius = 40;

    Vector2 chosen = { -1, -1 };

    GetSessionDimensions(&width, &height, info.sessionID);

    int size = 0;
    Texture2D* texture = LoadTextures(&size);
    Texture2D city[2];

    Camera2D camera1 = createCamera(width, height, radius);

    RenderTexture screenCamera1 = LoadRenderTexture(GetScreenWidth(), GetScreenHeight() + 20);
    Rectangle splitScreenRect = { 0.0f, 0.0f, (float)screenCamera1.texture.width, (float)-screenCamera1.texture.height };

    struct GridTile** grid = allocSessionGridTile(width, height, texture, info.sessionID);

    struct Civilization* civilizations = GetSessionCivilizations(info.sessionID);

    bool political = true;
    int position = 1;
    char playerName[512] = { 0 };
    char civilizationName[512] = { 0 };
    int playerID = 0;
    int civilizationID = 0;
    int civilizationNr = 0;
    char topBuffor[512] = { 0 };

    bool updatePlayer = true;

    struct provinceInformation provinceInfo = { 0 };

    GetSessionPoliticalDivision(grid, info.sessionID);

    addCityTexture(city, size);
    ShowPlayer(playerName, civilizationName, &playerID, &civilizationID, info.sessionID, position);
    civilizationNr = getNr(civilizations, civilizationID);
    sprintf(topBuffor, "%s - %s", playerName, civilizationName);

    while (!WindowShouldClose() && *state == PLAY) {
        if (IsKeyPressed(KEY_A)) if (position > 1) {
            position -= 1;
            updatePlayer = true;
        }
        if (IsKeyPressed(KEY_D)) {
            if (ShowPlayer(playerName, civilizationName, &playerID, &civilizationID, info.sessionID, position + 1)) {
                position += 1;
            }
            updatePlayer = true;
        }

        if (updatePlayer) {
            ShowPlayer(playerName, civilizationName, &playerID, &civilizationID, info.sessionID, position);
            civilizationNr = getNr(civilizations, civilizationID);
            sprintf(topBuffor, "%s - %s", playerName, civilizationName);
            updatePlayer = false;
            chosen = (Vector2){ -1, -1 };
            camera1 = createCamera(width, height, radius);
        }

        if (IsKeyDown(KEY_LEFT)) camera1.target.x -= 1 / camera1.zoom;
        if (IsKeyDown(KEY_RIGHT)) camera1.target.x += 1 / camera1.zoom;
        if (IsKeyDown(KEY_DOWN)) camera1.target.y += 1 / camera1.zoom;
        if (IsKeyDown(KEY_UP)) camera1.target.y -= 1 / camera1.zoom;

        if (IsKeyDown(KEY_Q)) camera1.zoom += 0.01f;
        if (IsKeyDown(KEY_E)) camera1.zoom -= 0.01f;
        camera1.zoom += (GetMouseWheelMove() * camera1.zoom / 16);
        if (camera1.zoom < 0.1) camera1.zoom = 0.1f;
        if (camera1.zoom > 10) camera1.zoom = 10.0f;

        BeginTextureMode(screenCamera1);
            ClearBackground(BROWN);

            BeginMode2D(camera1);
                GenerateHexGrid(radius, width, height, grid);
                DrawVisibleFields(radius, width, height, grid, city);
                if (political) {
                    DrawPoliticalDivision(radius, width, height, grid, civilizations);
                    DrawCity(radius, width, height, grid, city);
                }
                if (topLayer.indivLayers.countryInfo) DrawClickedCivilization(radius, width, height, grid);
                if (topLayer.indivLayers.provinceInfo) DrawClickedProvince(radius, width, height, grid);
                DrawNormalPoliticalGridOutline(radius, width, height, grid, civilizationID, civilizations[civilizationNr].color);
                if (topLayer.indivLayers.countryInfo)
                if (grid[(int)chosen.x][(int)chosen.y].civilizationID > 0) 
                    DrawChosenPoliticalGridOutline(radius, width, height, grid, grid[(int)chosen.x][(int)chosen.y].civilizationID);
                DrawHexGridOutline(radius, width, height, grid);
                drawMenuElement(topBuffor, radius * 2, (int)(sqrtf(3) * radius * width / 2.0), -radius, 10, 10, NULL, NULL);
            EndMode2D();

            DrawRectangle(0, 0, GetScreenWidth(), 40, (Color) { .r = 0, .g = 0, .b = 0, .a = 230 });
            DrawText(TextFormat("%-20s", playerName), 0, 5, 20, RAYWHITE);
            if (position == 1) DrawText("Next Tur", GetScreenWidth() - MeasureText("Next Tur", 20), 5, 20, RAYWHITE);
            if (topLayer.indivLayers.provinceInfo) {
                DrawRectangle(0, GetScreenHeight() >> 1, GetScreenWidth() >> 1, GetScreenHeight() >> 1, (Color) { .r = 0, .g = 0, .b = 0, .a = 230 });
                DrawText(TextFormat("Terrain: %s", provinceInfo.terrainName), 0, (GetScreenHeight() >> 1) + 50, 20, RAYWHITE);
                DrawText(TextFormat("Region: %s", (*provinceInfo.regionName == 0) ? "None" : provinceInfo.regionName), 0, (GetScreenHeight() >> 1) + 90, 20, RAYWHITE);
                DrawText(TextFormat("City: %s", (*provinceInfo.cityName == 0) ? "None" : provinceInfo.cityName), 0, (GetScreenHeight() >> 1) + 130, 20, RAYWHITE);
            }
            else if (topLayer.indivLayers.countryInfo) if (grid[(int)chosen.x][(int)chosen.y].civilizationID > 0) {
                DrawRectangle(0, GetScreenHeight() >> 2, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + (GetScreenHeight() >> 2), (Color) { .r = 0, .g = 0, .b = 0, .a = 230 });
            }
        EndTextureMode();

        BeginDrawing();

        ClearBackground(BROWN);
        DrawTextureRec(screenCamera1.texture, splitScreenRect, (Vector2) { 0, 0 }, WHITE);

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            checkClick(height, width, radius, grid, &chosen, camera1);
            if (chosen.x != -1) { 
                GetProvinceInformation(info.sessionID, (int)chosen.x, (int)chosen.y, &provinceInfo); 
                topLayer.indivLayers.provinceInfo = 1;
            }
            else {
                topLayer.layers = 0;
            }
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            checkClick(height, width, radius, grid, &chosen, camera1);
            if (chosen.x != -1) {
                topLayer.indivLayers.countryInfo = 1;
            }
            else {
                topLayer.layers = 0;
            }
        }

        if (IsKeyPressed(KEY_P)) {
            Pause(state, PLAY, &screenCamera1, &splitScreenRect);
        }

        if (IsKeyPressed(KEY_M)) {
            political = !political;
        }
    }

    free(civilizations);
    UnloadRenderTexture(screenCamera1);
    UnloadTextures(texture, size);
    UnloadTexture(city[0]);
    UnloadTexture(city[1]);
}