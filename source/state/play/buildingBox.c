#include <stdbool.h>

#include <raylib.h>

#include "play.h"

#include "isMouseInRange.h"
#include "drawMenuElement.h"
#include "GameSession.h"

bool clickBuildingLayer(union layers* topLayer, Rectangle buildingRec) {
    bool result = false;

    if (topLayer->indivLayers.buildingInfo && CheckCollisionPointRec(GetMousePosition(), buildingRec)) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseInRange((GetScreenWidth() >> 1) - 30, (GetScreenHeight() >> 2) + 30, 5, 5, 20, "x")) {
                topLayer->layers = 0;
            }

            result = true;
        }
    }

    return result;
}

bool drawBuildingInfo(union layers topLayer, Rectangle buildingRec, struct building building[]) {
    bool result = false;

    if (topLayer.indivLayers.buildingInfo) {
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

        result = true;
    }

    return result;
}