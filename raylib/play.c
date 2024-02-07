#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "raylib.h"

#include "state.h"
#include "position.h"

#include "drawMenuElement.h"
#include "modifyBackgroundColor.h"

void play(enum state* state) {
    
    Color color = { .a = 255, .b = 100, .r = 100, .g = 100 };
    Color color2 = { .a = 255, .b = 50, .g = 215, .r = 78 };
    Color color3 = { .a = 105, .b = 50, .g = 215, .r = 78 };
    static struct position cubePosition = { .x = 0, .y = 0, .incX = 1, .incY = 1 };

    *state = PLAY;
    while (!WindowShouldClose() && *state == PLAY) {
        BeginDrawing();

        ClearBackground((Color) { .r = 0, .g = 0, .b = 0, .a = 0 });
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), color);

        drawMenuElement("Games", 20, GetScreenWidth() >> 1, GetScreenHeight() >> 3, 10, 10, &color2, &color2);
        drawMenuElement("Create New Game", 20, (GetScreenWidth() >> 1) - 100, (GetScreenHeight() >> 1) + 150, 10, 10, &color2, &color3);
        drawMenuElement("Load Game", 20, (GetScreenWidth() >> 1) + 75, (GetScreenHeight() >> 1) + 150, 10, 10, &color2, &color3);
        drawMenuElement("Back", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 200, 10, 10, &color2, &color3);

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            clickAndChangeState(state, "Create New Game", 20, (GetScreenWidth() >> 1) - 100, (GetScreenHeight() >> 1) + 150, 10, 10, CREATE_NEW_GAME);
            clickAndChangeState(state, "Load Game", 20, (GetScreenWidth() >> 1) + 75, (GetScreenHeight() >> 1) + 150, 10, 10, LOAD_GAME);
            clickAndChangeState(state, "Back", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 200, 10, 10, MENU);
        }

        moveCube(&cubePosition);
    }
}