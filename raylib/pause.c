#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "raylib.h"

#include "state.h"
#include "position.h"

#include "drawMenuElement.h"

void pause(enum state* state, Color* color, struct position cubePosition) {
    char buffor[128];
    Color cube = { .r = 255, .g = 255, .b = 255, .a = 255 };

    *state = PAUSE;
    do {
        BeginDrawing();
        //ClearBackground(*color);
        ClearBackground((Color) { .r = 0, .g = 0, .b = 0, .a = 0 });
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), *color);


        sprintf(buffor, "RGBA = (%u, %u, %u, %u)", color->r, color->g, color->b, color->a);
        DrawText(buffor, 0, 0, 20, (Color) { .b = 42, .g = 58, .r = 45, .a = 255 });

        DrawRectangle(cubePosition.x, cubePosition.y, 20, 20, cube);

        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color) { .r = 100, .g = 100, .b = 100, .a = 200 });

        drawMenuElement("Paused", 40, GetScreenWidth() >> 1, GetScreenHeight() >> 1, 10, 10, NULL, NULL);

        drawMenuElement("Resume", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 80, 10, 10, NULL, &(Color) {.a = 255, .b = 0, .r = 0, .g = 0 });
        drawMenuElement("Exit to Menu", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 130, 10, 10, NULL, &(Color) {.a = 255, .b = 0, .r = 0, .g = 0 });
        drawMenuElement("Exit", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 180, 10, 10, NULL, &(Color) {.a = 255, .b = 0, .r = 0, .g = 0 });
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            clickAndChangeState(state, "Resume", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 80, 10, 10, CUBE);
            clickAndChangeState(state, "Exit to Menu", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 130, 10, 10, MENU);
            clickAndChangeState(state, "Exit", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 180, 10, 10, EXIT);
        }
        if (IsKeyPressed(KEY_P)) {
            *state = CUBE;
        }
    } while (*state == PAUSE && !WindowShouldClose());
}

void Pause(enum state* state, enum state resumeState, RenderTexture* screenCamera1, Rectangle* splitScreenRect) {
    Color color1 = { .r = 100, .g = 100, .b = 100, .a = 200 };
    Color color2 = { .r = 0, .g = 0, .b = 0, .a = 255 };

    *state = PAUSE;
    do {
        BeginDrawing();

        ClearBackground(color1);
        if (screenCamera1 != NULL) DrawTextureRec(screenCamera1->texture, *splitScreenRect, (Vector2) { 0, 0 }, WHITE);
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight() + 100, color1);
        //ClearBackground(color1);

        drawMenuElement("Paused", 40, GetScreenWidth() >> 1, GetScreenHeight() >> 1, 10, 10, NULL, NULL);

        drawMenuElement("Resume", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 80, 10, 10, NULL, &color2);
        drawMenuElement("Exit to Menu", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 130, 10, 10, NULL, &color2);
        drawMenuElement("Exit", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 180, 10, 10, NULL, &color2);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            clickAndChangeState(state, "Resume", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 80, 10, 10, resumeState);
            clickAndChangeState(state, "Exit to Menu", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 130, 10, 10, MENU);
            clickAndChangeState(state, "Exit", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 180, 10, 10, EXIT);
        }
        if (IsKeyPressed(KEY_P)) {
            *state = resumeState;
        }
    } while (*state == PAUSE && !WindowShouldClose());
}