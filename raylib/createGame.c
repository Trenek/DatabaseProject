#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "raylib.h"

#include "state.h"
#include "inputBox.h"

#include "drawMenuElement.h"
#include "createGameSession.h"

void createGame(enum state* state) {
    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };
    struct inputBox saveName = { .text = "\0", .length = 0, .coordinates = { GetScreenWidth() / 2.0f - 200, (float)(GetScreenHeight() >> 1) - 150, 400, 30 }, .frontSize = 20 };
    extern int loggedInID;
    extern int gameSessionID;
    char errorMessage[512] = { 0 };
    int clicked = 0;

    while (!WindowShouldClose() && *state == CREATE_NEW_GAME) {
        BeginDrawing();

        ClearBackground(color);

        drawMenuElement("Create Game", 20, GetScreenWidth() >> 1, GetScreenHeight() >> 3, 10, 10, &color2, &color2);

        drawMenuElement("Save Name", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) - 175, 10, 10, NULL, NULL);
        DrawInputBox(&saveName);

        if (clicked == 1) drawTextWithBoxBehind(errorMessage, 20, (GetScreenWidth() >> 1), (GetScreenHeight() >> 1) + 70, 400, 40, &(Color) {.r = 255, .g = 255, .b = 255, .a = 255 });

        drawMenuElement("Create Game", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 150, 10, 10, &color2, &color3);
        drawMenuElement("Back", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 200, 10, 10, &color2, &color3);

        drawMenuElement("Back", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 200, 10, 10, &color2, &color3);

        EndDrawing();

        updateInputBox(&saveName);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseInRange(GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 150, 10, 10, 20, "Create New Game")) {
                gameSessionID = createGameSession(saveName.text, loggedInID, errorMessage);

                if (*errorMessage == 0) {
                    sprintf(errorMessage, "Save Created Successfully!");
                    *state = GAME_SETUP;
                }

                clicked = 1;
            }

            clickAndChangeState(state, "Back", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 200, 10, 10, LOAD_GAME);
        }
    }
}