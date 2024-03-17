#include <stdbool.h>
#include <raylib.h>

#include "play.h"

bool drawErrorLayer(union layers topLayer, char* errorMessage) {
    bool result = false;

    if (topLayer.indivLayers.errorLayer) {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), RED);
        DrawText(errorMessage, (GetScreenWidth() - MeasureText(errorMessage, 60)) >> 1, GetScreenHeight() >> 1, 60, RAYWHITE);
        DrawText("Click anything to continue", (GetScreenWidth() - MeasureText("Click anything to continue", 30)) >> 1, (GetScreenHeight() >> 1) + (GetScreenHeight() >> 2), 30, RAYWHITE);

        result = true;
    }

    return result;
}
