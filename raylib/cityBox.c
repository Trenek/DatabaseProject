#include <stdbool.h>
#include <stdio.h>
#include <raylib.h>

#include "play.h"
#include "gameInformations.h"
#include "inputBox.h"

#include "drawMenuElement.h"
#include "isMouseInRange.h"
#include "GameSession.h"

bool clickCityNameBox(union layers* topLayer, char* errorMessage, Rectangle cityNameRec, Vector2 chosen, struct inputBox *cityName, int* gold, bool* updatePlayer, struct gameInformations info) {
    bool result = false;

    if (topLayer->indivLayers.cityNameBox && CheckCollisionPointRec(GetMousePosition(), cityNameRec)) {
        updateInputBox(cityName);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseInRange(GetScreenWidth() / 2, (GetScreenHeight() >> 1) + 50, 10, 10, 20, "Commit and Pay 500")) {
                *errorMessage = 0;
                BuildCity(errorMessage, info.sessionID, (int)chosen.x, (int)chosen.y, cityName->text);
                if (*errorMessage) {
                    topLayer->layers = 0;
                    topLayer->indivLayers.errorLayer = 1;
                }
                else if (*gold < 500) {
                    topLayer->layers = 0;
                    topLayer->indivLayers.errorLayer = 1;
                    sprintf(errorMessage, "%s", "Not enought money!");
                }
                else {
                    *updatePlayer = 1;
                }
                topLayer->indivLayers.cityNameBox = 0;
            }
            result = true;
        }
    }

    return result;
}

bool drawCityNameBox(union layers topLayer, Rectangle cityNameRec, struct inputBox* cityName) {
    bool result = false;

    if (topLayer.indivLayers.cityNameBox) {
        DrawRectangleRec(cityNameRec, GREEN);
        DrawInputBox(cityName);
        drawMenuElement("Commit and Pay 500", 20, GetScreenWidth() / 2, (GetScreenHeight() >> 1) + 50, 10, 10, &BLUE, &GREEN);

        result = true;
    }

    return result;
}