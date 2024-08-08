#include <stdbool.h>

#include <raylib.h>

#include "GetProvinceInformation.h"
#include "play.h"
#include "GridTileDef.h"
#include "GameSession.h"

#include "drawMenuElement.h"
#include "isMouseInRange.h"

bool clickProvinceLayer(union layers* topLayer, Vector2 chosen, struct provinceInformation provinceInfo, Rectangle provinceRec, char constructionDate[], struct GridTile** grid, struct building building[], int civilizationID) {
    bool result = false;

    if (topLayer->indivLayers.provinceInfo && CheckCollisionPointRec(GetMousePosition(), provinceRec)) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseInRange((GetScreenWidth() >> 1) - 30, (GetScreenHeight() >> 1) + 30, 5, 5, 20, "x")) {
                topLayer->layers = 0;
            }
            else if (*provinceInfo.cityName) {
                if (isMouseInRange((MeasureText("Buildings", 20) >> 1) + 20, (GetScreenHeight() >> 1) + 170, 10, 10, 20, "Buildings")) {
                    topLayer->layers = 0;
                    topLayer->indivLayers.buildingInfo = 1;
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
                        topLayer->indivLayers.cityNameBox = 1;
                    }
            }
            result = true;
        }
    }

    return result;
}

bool drawProvinceInfo(union layers topLayer, Rectangle provinceRec, struct provinceInformation provinceInfo, char* constructionDate, struct GridTile** grid, Vector2 chosen, int civilizationID) {
    bool result = false;

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

        result = true;
    }

    return result;
}