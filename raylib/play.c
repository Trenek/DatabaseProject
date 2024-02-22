#include <stdlib.h>
#include <stdio.h>

#include <raylib.h>

#include "state.h"
#include "gameInformations.h"
#include "GridTileDef.h"
#include "inputBox.h"

#include "drawMenuElement.h"
#include "ProvinceTextures.h"
#include "createCamera.h"

#include "getDimensions.h"
#include "GetPoliticalDivision.h"
#include "Player.h"
#include "GetProvinceInformation.h"
#include "GameSession.h"
#include "GetProvinces.h"

union layers {
    struct layersS {
        unsigned char provinceInfo : 1;
        unsigned char countryInfo : 1;
        unsigned char buildingInfo : 1;
        unsigned char cityNameBox : 1;
        unsigned char errorLayer : 1;
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
    struct building building[8] = { 0 };

    bool political = true;
    int position = 1;
    char playerName[512] = { 0 };
    char civilizationName[512] = { 0 };
    int playerID = 0;
    int civilizationID = 0;
    int civilizationNr = 0;
    int gold = 0;
    char topBuffor[512] = { 0 };

    bool updatePlayer = true;

    struct provinceInformation provinceInfo = { 0 };
    Rectangle provinceRec = { 0, GetScreenHeight() >> 1, GetScreenWidth() >> 1, GetScreenHeight() >> 1 };
    Rectangle buildingRec = { 0, GetScreenHeight() >> 2, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + (GetScreenHeight() >> 2) };
    //Rectangle provinceExit = { (GetScreenWidth() >> 1) - 40, (GetScreenHeight() >> 1) + 20, 20, 20 };
    Rectangle countryRec = { 0, GetScreenHeight() >> 2, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + (GetScreenHeight() >> 2) };
    Rectangle topRec = { 0, 0, GetScreenWidth(), 40 };
    Rectangle cityNameRec = { GetScreenWidth() / 2.0f - 220, (float)(GetScreenHeight() >> 1) - 20, 440, 120 };

    char date[512] = { 0 };
    char constructionDate[512] = { 0 };
    char errorMessage[512] = { 0 };

    struct inputBox cityName = { .text = "\0", .length = 0, .coordinates = { GetScreenWidth() / 2.0f - 200, (float)(GetScreenHeight() >> 1), 400, 30 }, .frontSize = 20 };

    GetSessionPoliticalDivision(grid, info.sessionID);

    addCityTexture(city, size);
    ShowPlayer(playerName, civilizationName, &playerID, &civilizationID, &gold, info.sessionID, position);
    civilizationNr = getNr(civilizations, civilizationID);
    sprintf(topBuffor, "%s - %s", playerName, civilizationName);

    while (!WindowShouldClose() && *state == PLAY) {
        if (updatePlayer) {
            GetSessionProvinces(grid, texture, info.sessionID);
            GetSessionPoliticalDivision(grid, info.sessionID);
            ShowPlayer(playerName, civilizationName, &playerID, &civilizationID, &gold, info.sessionID, position);
            if (position == 1) GetCurrentDate(date, info.sessionID);
            civilizationNr = getNr(civilizations, civilizationID);
            sprintf(topBuffor, "%s - %s", playerName, civilizationName);
            updatePlayer = false;
            chosen = (Vector2){ -1, -1 };
            topLayer.layers = 0;
        }

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
                    DrawChosenPoliticalGridOutline(radius, width, height, grid, grid[(int)chosen.x][(int)chosen.y].civilizationID);
                DrawHexGridOutline(radius, width, height, grid);
                drawMenuElement(topBuffor, radius * 2, (int)(sqrtf(3) * radius * width / 2.0), -radius, 10, 10, NULL, NULL);
            EndMode2D();

            DrawRectangleRec(topRec, (Color) { .r = 0, .g = 0, .b = 0, .a = 230 });
            DrawText(TextFormat("%-20s", playerName), 10, 10, 20, RAYWHITE);
            DrawText(TextFormat("Gold: %i", gold), 100, 10, 20, RAYWHITE);
            if (position == 1) drawMenuElement(date, 20, GetScreenWidth() - (MeasureText(date, 20) / 2) - 10, 10, 5, 5, NULL, &RAYWHITE);
            if (topLayer.indivLayers.provinceInfo) {
                DrawRectangleRec(provinceRec, (Color) { .r = 0, .g = 0, .b = 0, .a = 230 });
                //DrawRectangleRec(provinceExit, RED);
                drawMenuElement("x", 20, (GetScreenWidth() >> 1) - 30, (GetScreenHeight() >> 1) + 30, 5, 5, &RED, &BLUE);
                DrawText(TextFormat("Terrain: %s", provinceInfo.terrainName), 20, (GetScreenHeight() >> 1) + 50, 20, RAYWHITE);
                DrawText(TextFormat("Region: %s", (*provinceInfo.regionName == 0) ? "None" : provinceInfo.regionName), 20, (GetScreenHeight() >> 1) + 90, 20, RAYWHITE);
                DrawText(TextFormat("City: %s", (*provinceInfo.cityName == 0) ? "None" : provinceInfo.cityName), 20, (GetScreenHeight() >> 1) + 130, 20, RAYWHITE);
                if (*constructionDate) {
                    drawMenuElement(TextFormat("Complete at %s", constructionDate), 20, (MeasureText(TextFormat("Complete at %s", constructionDate), 20) >> 1) + 20, (GetScreenHeight() >> 1) + 170, 10, 10, &GREEN, &RED);
                    if (isMouseInRange((MeasureText(TextFormat("Complete at %s", constructionDate), 20) >> 1) + 20, (GetScreenHeight() >> 1) + 170, 10, 10, 20, TextFormat("Complete at %s", constructionDate))) {
                        DrawRectangle(GetMouseX(), GetMouseY(), MeasureText("Cancel", 20) + 20, 30, VIOLET);
                        DrawText("Cancel", GetMouseX() + 10, GetMouseY() + 10, 20, RAYWHITE);
                    }
                }
                else if (*provinceInfo.cityName) {
                    drawMenuElement("Buildings", 20, (MeasureText("Buildings", 20) >> 1) + 20, (GetScreenHeight() >> 1) + 170, 10, 10, &RED, &GREEN);
                }
                else {
                    if (grid[(int)chosen.x][(int)chosen.y].civilizationID == civilizationID) {
                        drawMenuElement("Build City", 20, (MeasureText("Build City", 20) >> 1) + 20, (GetScreenHeight() >> 1) + 170, 10, 10, &RED, &GREEN);
                    }
                    else {
                        drawMenuElement("Build City", 20, (MeasureText("Build City", 20) >> 1) + 20, (GetScreenHeight() >> 1) + 170, 10, 10, &GRAY, &GRAY);
                    }
                }
            }
            else if (topLayer.indivLayers.buildingInfo) {
                DrawRectangleRec(buildingRec, (Color) { .r = 0, .g = 0, .b = 0, .a = 230 });
                drawMenuElement("x", 20, (GetScreenWidth() >> 1) - 30, (GetScreenHeight() >> 2) + 30, 5, 5, &RED, &BLUE);
                for (int i = 0; i < 8; i += 1) {
                    drawMenuElement(TextFormat("%s: Level: %i/%i, Tax: %i, Levi : %i", building[i].name, building[i].level, building[i].maxLevel, building[i].tax, building[i].levies), 15, (MeasureText(TextFormat("%s: Level: %i/%i, Tax: %i, Levi : %i", building[i].name, building[i].level, building[i].maxLevel, building[i].tax, building[i].levies), 15) >> 1) + 20, (GetScreenHeight() >> 2) + 100 + (40 * i), 10, 10, &BLACK, &VIOLET);
                }
                for (int i = 0; i < 8; i += 1) {
                    if (isMouseInRange((MeasureText(TextFormat("%s: Level: %i/%i, Tax: %i, Levi : %i", building[i].name, building[i].level, building[i].maxLevel, building[i].tax, building[i].levies), 15) >> 1) + 20, (GetScreenHeight() >> 2) + 100 + (40 * i), 10, 10, 15, TextFormat("%s: Level: %i/%i, Tax: %i, Levi : %i", building[i].name, building[i].level, building[i].maxLevel, building[i].tax, building[i].levies))) {
                        DrawRectangle(GetMouseX(), GetMouseY(), MeasureText(TextFormat("Update for %i", building[i].price), 20) + 20, 50, RED);
                        DrawText(TextFormat("Update for %i", building[i].price), GetMouseX() + 10, GetMouseY() + 10, 20, RAYWHITE);
                    }
                }
            }
            else if (topLayer.indivLayers.countryInfo) {
                DrawRectangleRec(countryRec, (Color) { .r = 0, .g = 0, .b = 0, .a = 230 });
                drawMenuElement("x", 20, (GetScreenWidth() >> 1) - 30, (GetScreenHeight() >> 2) + 30, 5, 5, &RED, &BLUE);
            }

            if (topLayer.indivLayers.cityNameBox) {
                DrawRectangleRec(cityNameRec, GREEN);
                DrawInputBox(&cityName);
                drawMenuElement("Commit and Pay 500", 20, GetScreenWidth() / 2, (GetScreenHeight() >> 1) + 50, 10, 10, &BLUE, &GREEN);
            }
            else if (topLayer.indivLayers.errorLayer) {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), RED);
                DrawText(errorMessage, (GetScreenWidth() - MeasureText(errorMessage, 60)) >> 1, GetScreenHeight() >> 1, 60, RAYWHITE);
                DrawText("Click anything to continue", (GetScreenWidth() - MeasureText("Click anything to continue", 30)) >> 1, (GetScreenHeight() >> 1) + (GetScreenHeight() >> 2), 30, RAYWHITE);
            }

        EndTextureMode();

        BeginDrawing();

        ClearBackground(BROWN);
        DrawTextureRec(screenCamera1.texture, splitScreenRect, (Vector2) { 0, 0 }, WHITE);

        EndDrawing();

        SetMouseCursor(checkCoursor(&cityName) ? MOUSE_CURSOR_IBEAM : MOUSE_CURSOR_DEFAULT);
        updateInputBox(&cityName);

        if (topLayer.indivLayers.cityNameBox && CheckCollisionPointRec(GetMousePosition(), cityNameRec)) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (isMouseInRange(GetScreenWidth() / 2, (GetScreenHeight() >> 1) + 50, 10, 10, 20, "Commit and Pay 500")) {
                    *errorMessage = 0;
                    BuildCity(errorMessage, info.sessionID, (int)chosen.x, (int)chosen.y, cityName.text);
                    if (*errorMessage) {
                        topLayer.layers = 0;
                        topLayer.indivLayers.errorLayer = 1;
                    }
                    else if (gold < 500) {
                        topLayer.layers = 0;
                        topLayer.indivLayers.errorLayer = 1;
                        sprintf(errorMessage, "%s", "Not enought money!");
                    }
                    else {
                        updatePlayer = 1;
                    }
                    topLayer.indivLayers.cityNameBox = 0;
                }
            }
        }
        else if ((position == 1) && CheckCollisionPointRec(GetMousePosition(), topRec)) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (isMouseInRange(GetScreenWidth() - (MeasureText(date, 20) / 2) - 10, 10, 5, 5, 20, date)) {
                    UpdateCurrentDate(info.sessionID);
                    updatePlayer = 1;
                }
            }
        }
        else if (topLayer.indivLayers.provinceInfo && CheckCollisionPointRec(GetMousePosition(), provinceRec)) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (isMouseInRange((GetScreenWidth() >> 1) - 30, (GetScreenHeight() >> 1) + 30, 5, 5, 20, "x")) {
                    topLayer.layers = 0;
                }
                else if (*provinceInfo.cityName) {
                    if (isMouseInRange((MeasureText("Buildings", 20) >> 1) + 20, (GetScreenHeight() >> 1) + 170, 10, 10, 20, "Buildings")) {
                        topLayer.layers = 0;
                        topLayer.indivLayers.buildingInfo = 1;
                        GetBuildingType(grid[(int)chosen.x][(int)chosen.y].CityID, 1, building[0].page, building + 0);
                        GetBuildingType(grid[(int)chosen.x][(int)chosen.y].CityID, 2, building[1].page, building + 1);
                        GetBuildingType(grid[(int)chosen.x][(int)chosen.y].CityID, 3, building[2].page, building + 2);
                        GetBuildingType(grid[(int)chosen.x][(int)chosen.y].CityID, 4, building[3].page, building + 3);
                        GetBuildingType(grid[(int)chosen.x][(int)chosen.y].CityID, 5, building[4].page, building + 4);
                        GetBuildingType(grid[(int)chosen.x][(int)chosen.y].CityID, 6, building[5].page, building + 5);
                        GetBuildingType(grid[(int)chosen.x][(int)chosen.y].CityID, 7, building[6].page, building + 6);
                        GetBuildingType(grid[(int)chosen.x][(int)chosen.y].CityID, 8, building[7].page, building + 7);
                    }
                }
                else if (*constructionDate) {

                }
                else {
                    if (grid[(int)chosen.x][(int)chosen.y].civilizationID == civilizationID) 
                    if (isMouseInRange((MeasureText("Build City", 20) >> 1) + 20, (GetScreenHeight() >> 1) + 170, 10, 10, 20, "Build City")) {
                        topLayer.indivLayers.cityNameBox = 1;
                    }
                }
            }
        }
        else if (topLayer.indivLayers.buildingInfo && CheckCollisionPointRec(GetMousePosition(), buildingRec)) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (isMouseInRange((GetScreenWidth() >> 1) - 30, (GetScreenHeight() >> 2) + 30, 5, 5, 20, "x")) {
                    topLayer.layers = 0;
                }
            }
        }
        else if (topLayer.indivLayers.countryInfo && CheckCollisionPointRec(GetMousePosition(), countryRec)) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (isMouseInRange((GetScreenWidth() >> 1) - 30, (GetScreenHeight() >> 2) + 30, 5, 5, 20, "x")) {
                    topLayer.layers = 0;
                }
            }
        }
        else {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                checkClick(height, width, radius, grid, &chosen, camera1);
                topLayer.layers = 0;
                if (chosen.x != -1) {
                    *constructionDate = 0;
                    GetProvinceInformation(info.sessionID, (int)chosen.x, (int)chosen.y, &provinceInfo);
                    GetCityConstructionDate(constructionDate, info.sessionID, (int)chosen.x, (int)chosen.y);
                    topLayer.indivLayers.provinceInfo = 1;
                }
            }
            else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                checkClick(height, width, radius, grid, &chosen, camera1);
                topLayer.layers = 0;
                if (chosen.x != -1)
                if (grid[(int)chosen.x][(int)chosen.y].civilizationID > 0) {
                    topLayer.indivLayers.countryInfo = 1;
                }
            }
        }

        if (!topLayer.indivLayers.cityNameBox) {
            if (IsKeyPressed(KEY_A)) if (position > 1) {
                position -= 1;
                updatePlayer = true;
            }
            if (IsKeyPressed(KEY_D)) {
                if (ShowPlayer(playerName, civilizationName, &playerID, &civilizationID, &gold, info.sessionID, position + 1)) {
                    position += 1;
                }
                updatePlayer = true;
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

            if (IsKeyPressed(KEY_P)) {
                Pause(state, PLAY, &screenCamera1, &splitScreenRect);
            }

            if (IsKeyPressed(KEY_M)) {
                political = !political;
            }
        }
    }

    free(civilizations);
    UnloadRenderTexture(screenCamera1);
    UnloadTextures(texture, size);
    UnloadTexture(city[0]);
    UnloadTexture(city[1]);
}