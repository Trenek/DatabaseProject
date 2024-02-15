#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "raylib.h"

#include "state.h"
#include "gameInformations.h"

#include "drawMenuElement.h"
#include "getGameSessions.h"

inline Rectangle getRectangle(int x, int y, int incX, int incY) {
    return (Rectangle) { .x = (float)(x - (incX >> 1)), .y = (float)(y - (incY >> 2)), .width = (float)incX, .height = (float)incY };
}

void loadGame(enum state* state) {
    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };
    struct gameSession gameSessions[10];
    char buffer[128];
    int i = 0;
    int page = 1;
    int nextExists = 0;
    int chosenOne = -1;
    int chosenPage = 0;
    extern struct gameInformations info;

    nextExists = GetGameSessions(gameSessions, page + 1, info.owner);
    GetGameSessions(gameSessions, page, info.owner);
    while (!WindowShouldClose() && *state == LOAD_GAME) {
        BeginDrawing();

        ClearBackground(color);

        drawMenuElement("Games", 20, GetScreenWidth() >> 1, GetScreenHeight() >> 3, 10, 10, &color2, &color2);
        if (page > 1) drawMenuElement("Previous", 20, (GetScreenWidth() >> 1) - 100, (GetScreenHeight() >> 3), 10, 10, &color2, &color3);
        if (nextExists) drawMenuElement("Next", 20, (GetScreenWidth() >> 1) + 80, (GetScreenHeight() >> 3), 10, 10, &color2, &color3);

        i = 0;
        while (i < 10) {
            sprintf(buffer, gameSessions[i].nr ? "%3i. %-30s" : " ", gameSessions[i].nr, gameSessions[i].name);
            drawTextWithBoxBehind(buffer, 15, GetScreenWidth() >> 1, (GetScreenHeight() >> 3) + ((i + 1) * 33) + 30, 250, 30, (chosenOne == i && chosenPage == page) ? &color3 : &color2);
            i += 1;
        }

        drawMenuElement("Create New Game", 20, (GetScreenWidth() >> 1) - 100, (GetScreenHeight() >> 1) + 200, 10, 10, &color2, &color3);
        drawMenuElement("Load Game", 20, (GetScreenWidth() >> 1) + 75, (GetScreenHeight() >> 1) + 200, 10, 10, &color2, page == chosenPage ? &color3 : &color2);
        drawMenuElement("Back", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 250, 10, 10, &color2, &color3);

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (page > 1) {
                if (isMouseInRange((GetScreenWidth() >> 1) - 100, (GetScreenHeight() >> 3), 10, 10, 20, "Previous")) {
                    page -= 1;
                    nextExists = GetGameSessions(gameSessions, page + 1, info.owner);
                    GetGameSessions(gameSessions, page, info.owner);
                }
            }
            if (nextExists) {
                if (isMouseInRange((GetScreenWidth() >> 1) + 80, (GetScreenHeight() >> 3), 10, 10, 20, "Next")) {
                    page += 1;
                    nextExists = GetGameSessions(gameSessions, page + 1, info.owner);
                    GetGameSessions(gameSessions, page, info.owner);
                }
            }

            i = 0;
            while (i < 10) {
                if (CheckCollisionPointRec(GetMousePosition(), getRectangle(GetScreenWidth() >> 1, (GetScreenHeight() >> 3) + ((i + 1) * 33) + 30, 250, 30))) {
                    chosenPage = page;
                    chosenOne = i;
                    info.sessionID = gameSessions[i].id;
                }

                i += 1;
            }

            clickAndChangeState(state, "Create New Game", 20, (GetScreenWidth() >> 1) - 100, (GetScreenHeight() >> 1) + 200, 10, 10, CREATE_NEW_GAME);
            if (page == chosenPage) clickAndChangeState(state, "Load Game", 20, (GetScreenWidth() >> 1) + 75, (GetScreenHeight() >> 1) + 200, 10, 10, GAME_SETUP);
            clickAndChangeState(state, "Back", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 250, 10, 10, MENU);
        }
    }
}