#include <stdbool.h>
#include <stddef.h>
#include <raylib.h>

#include "drawMenuElement.h"
#include "isMouseInRange.h"
#include "GameSession.h"

#include "gameInformations.h"

void drawTopLayer(Rectangle topRec, char* playerName, int gold, int position, char* date) {
    DrawRectangleRec(topRec, (Color) { .r = 0, .g = 0, .b = 0, .a = 230 });
    DrawText(TextFormat("%-20s", playerName), 10, 10, 20, RAYWHITE);
    DrawText(TextFormat("Gold: %i", gold), 100, 10, 20, RAYWHITE);
    if (position == 1)
        drawMenuElement(date, 20, GetScreenWidth() - (MeasureText(date, 20) / 2) - 10, 10, 5, 5, NULL, &RAYWHITE);
}

bool clickDateForward(int position, Rectangle topRec, bool* updatePlayer, struct gameInformations info, char date[]) {
    bool result = false;

    if ((position == 1) && CheckCollisionPointRec(GetMousePosition(), topRec)) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseInRange(GetScreenWidth() - (MeasureText(date, 20) / 2) - 10, 10, 5, 5, 20, date)) {
                UpdateCurrentDate(info.sessionID);
                *updatePlayer = 1;
            }
            result = true;
        }
        else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            if (isMouseInRange(GetScreenWidth() - (MeasureText(date, 20) / 2) - 10, 10, 5, 5, 20, date)) {
                UpdateCurrentDateBy10Days(info.sessionID);
                *updatePlayer = 1;
            }
            result = true;
        }
    }

    return result;
}