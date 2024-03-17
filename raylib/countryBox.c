#include <stdbool.h>
#include <raylib.h>

#include "play.h"

#include "isMouseInRange.h"
#include "drawMenuElement.h"

bool clickCountryLayer(union layers* topLayer, Rectangle countryRec) {
    bool result = false;

    if (topLayer->indivLayers.countryInfo && CheckCollisionPointRec(GetMousePosition(), countryRec)) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseInRange((GetScreenWidth() >> 1) - 30, (GetScreenHeight() >> 2) + 30, 5, 5, 20, "x")) {
                topLayer->layers = 0;
            }

            result = true;
        }
    }

    return result;
}

bool drawCountryInfo(union layers topLayer, Rectangle countryRec) {
    bool result = false;

    if (topLayer.indivLayers.countryInfo) {
        DrawRectangleRec(countryRec, (Color) { .r = 0, .g = 0, .b = 0, .a = 230 });
        drawMenuElement("x", 20, (GetScreenWidth() >> 1) - 30, (GetScreenHeight() >> 2) + 30, 5, 5, &RED, &BLUE);

        result = true;
    }

    return result;
}