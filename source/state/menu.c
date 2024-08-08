#include <stdio.h>

#include <raylib.h>

#include "state.h"
#include "position.h"
#include "gameInformations.h"

#include "drawMenuElement.h"
#include "modifyBackgroundColor.h"

void menu(enum state* state) {
    static Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };
    static struct position cubePosition = { .x = 0, .y = 0, .incX = 1, .incY = 1 };
    char buffor[128];
    extern struct gameInformations info;

    while (!WindowShouldClose() && *state == MENU) {
        BeginDrawing();

        ClearBackground(color);

        drawMenuElement("Main Menu", 20, GetScreenWidth() >> 1, GetScreenHeight() >> 3, 10, 10, &color2, &color2);
        drawMenuElement("Play", 20, GetScreenWidth() >> 1, GetScreenHeight() >> 1, 10, 10, &color2, &color3);
        drawMenuElement("Register", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 50, 10, 10, &color2, &color3);
        drawMenuElement("Player List", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 100, 10, 10, &color2, &color3);
        drawMenuElement("Map Debug", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 150, 10, 10, &color2, &color3);
        drawMenuElement("Exit", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 200, 10, 10, &color2, &color3);
        drawMenuElement("Cube", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 250, 10, 10, &color2, &color3);

        drawMenuElement(info.owner == 0 ? "Log In" : "Log Out", 20, GetScreenWidth() - (GetScreenWidth() >> 4) - 10, (GetScreenHeight() >> 5), 10, 10, &color2, &color3);

        sprintf(buffor, "RGBA = (%u, %u, %u, %u)", color.r, color.g, color.b, color.a);
        DrawText(buffor, 0, 0, 20, (Color) { .b = 42, .g = 58, .r = 45, .a = 255 });

        DrawRectangle(cubePosition.x, cubePosition.y, 20, 20, (Color) { .r = 0, .g = 0, .b = 0, .a = 255 });
        EndDrawing();

        modifyBackgroundColor(&color);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            clickAndChangeState(state, "Play", 20, GetScreenWidth() >> 1, GetScreenHeight() >> 1, 10, 10, info.owner == 0 ? LOGIN : LOAD_GAME);
            clickAndChangeState(state, "Register", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 50, 10, 10, REGISTER);
            clickAndChangeState(state, "Player List", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 100, 10, 10, PLAYER_LIST);
            clickAndChangeState(state, "Map Debug", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 150, 10, 10, MAP_DEBUG);
            clickAndChangeState(state, "Exit", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 200, 10, 10, EXIT);
            clickAndChangeState(state, "Cube", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 250, 10, 10, CUBE);

            if (info.owner) {
                if (isMouseInRange(GetScreenWidth() - (GetScreenWidth() >> 3), (GetScreenHeight() >> 4) - 10, 10, 10, 20, "Log Out")) {
                    info.owner = 0;
                }
            }
            else {
                clickAndChangeState(state, "Log In", 20, GetScreenWidth() - (GetScreenWidth() >> 4), (GetScreenHeight() >> 5), 10, 10, LOGIN);
            }
        }

        moveCube(&cubePosition);
    }
}