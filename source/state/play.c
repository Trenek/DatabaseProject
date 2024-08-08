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

#include "play.h"

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

            drawTopLayer(topRec, playerName, gold, position, date);

            if (!drawProvinceInfo(topLayer, provinceRec, provinceInfo, constructionDate, grid, chosen, civilizationID))
            if (!drawBuildingInfo(topLayer, buildingRec, building))
                drawCountryInfo(topLayer, countryRec);

            if (!drawCityNameBox(topLayer, cityNameRec, &cityName))
                drawErrorLayer(topLayer, errorMessage);

        EndTextureMode();

        BeginDrawing();
            ClearBackground(BROWN);
            DrawTextureRec(screenCamera1.texture, splitScreenRect, (Vector2) { 0, 0 }, WHITE);
        EndDrawing();

        SetMouseCursor(topLayer.indivLayers.cityNameBox && checkCoursor(&cityName) ? MOUSE_CURSOR_IBEAM : MOUSE_CURSOR_DEFAULT);

        if (!clickCityNameBox(&topLayer, errorMessage, cityNameRec, chosen, &cityName, &gold, &updatePlayer, info))
        if (!clickDateForward(position, topRec, &updatePlayer, info, date))
        if (!clickProvinceLayer(&topLayer, chosen, provinceInfo, provinceRec, constructionDate, grid, building, civilizationID))
        if (!clickBuildingLayer(&topLayer, buildingRec))
        if (!clickCountryLayer(&topLayer, countryRec)) {
            mapClick(&topLayer, height, width, radius, grid, &chosen, camera1, constructionDate, &provinceInfo, info);
        }

        mapChange(&topLayer, &position, &updatePlayer, &camera1, state, screenCamera1, splitScreenRect, &political, playerName, civilizationName, &playerID, &civilizationID, &gold, info);
    }

    free(civilizations);
    UnloadRenderTexture(screenCamera1);
    UnloadTextures(texture, size);
    UnloadTexture(city[0]);
    UnloadTexture(city[1]);
}