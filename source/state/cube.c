#include <stdio.h>

#include <raylib.h>

#include "state.h"
#include "position.h"

#include "drawMenuElement.h"
#include "modifyBackgroundColor.h"

void cube(enum state* state) {
    static Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color cube = { .r = 255, .g = 255, .b = 255, .a = 255 };
    static struct position cubePosition = { .x = 0, .y = 0, .incX = 1, .incY = 1 };
    char buffor[128];

    while (!WindowShouldClose() && *state == CUBE) {
        BeginDrawing();
        //ClearBackground(color);
        ClearBackground((Color) { .r = 0, .g = 0, .b = 0, .a = 0 });
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), color);

        sprintf(buffor, "RGBA = (%u, %u, %u, %u)", color.r, color.g, color.b, color.a);
        DrawText(buffor, 0, 0, 20, (Color) { .b = 42, .g = 58, .r = 45, .a = 255 });

        drawMenuElement("Cube is Cubing", 40, GetScreenWidth() >> 1, GetScreenHeight() >> 1, 10, 10, NULL, NULL);

        DrawRectangle(cubePosition.x, cubePosition.y, 20, 20, cube);
        EndDrawing();

        if (IsKeyPressed(KEY_P)) {
            pause(state, &color, cubePosition);
        }

        modifyBackgroundColor(&color);

        moveCube(&cubePosition);
    }
}