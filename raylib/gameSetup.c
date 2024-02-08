#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "raylib.h"

#include "state.h"

#include "drawMenuElement.h"

void gameSetup(enum state* state) {
    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };

    while (!WindowShouldClose() && *state == GAME_SETUP) {
        BeginDrawing();

        ClearBackground(color);

        drawMenuElement("Game Setup", 20, GetScreenWidth() >> 1, GetScreenHeight() >> 3, 10, 10, &color2, &color2);
        drawMenuElement("Back", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 200, 10, 10, &color2, &color3);

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            clickAndChangeState(state, "Create New Game", 20, (GetScreenWidth() >> 1) - 100, (GetScreenHeight() >> 1) + 150, 10, 10, CREATE_NEW_GAME);
            clickAndChangeState(state, "Back", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 200, 10, 10, LOAD_GAME);
        }
    }
}