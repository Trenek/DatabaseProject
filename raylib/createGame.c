#include <stdio.h>

#include <raylib.h>

#include "state.h"
#include "inputBox.h"
#include "gameInformations.h"

#include "drawMenuElement.h"
#include "createGameSession.h"
#include "GetMaps.h"
#include "getGameSessions.h"

inline Rectangle getRectangle(int x, int y, int incX, int incY) {
    return (Rectangle) { .x = (float)(x - (incX >> 1)), .y = (float)(y - (incY >> 2)), .width = (float)incX, .height = (float)incY };
}

static void chooseMap(char* mapName, int* mapID) {
    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };
    struct map maps[10];
    char buffer[128];
    int i = 0;
    int page = 1;
    int nextExists = 0;
    int chosenOne = -1;
    int chosenPage = 0;
    int chosen = 0;

    nextExists = GetMaps(maps, page + 1);
    GetMaps(maps, page);
    while (!WindowShouldClose() && chosen == 0) {
        BeginDrawing();

        ClearBackground(color);

        drawMenuElement("Choose Map", 20, GetScreenWidth() >> 1, GetScreenHeight() >> 3, 10, 10, &color2, &color2);
        if (page > 1) drawMenuElement("Previous", 20, (GetScreenWidth() >> 1) - 100, (GetScreenHeight() >> 3), 10, 10, &color2, &color3);
        if (nextExists) drawMenuElement("Next", 20, (GetScreenWidth() >> 1) + 80, (GetScreenHeight() >> 3), 10, 10, &color2, &color3);

        i = 0;
        while (i < 10) {
            sprintf(buffer, maps[i].nr ? "%3i. %-30s" : " ", maps[i].nr, maps[i].name);
            drawTextWithBoxBehind(buffer, 15, GetScreenWidth() >> 1, (GetScreenHeight() >> 3) + ((i + 1) * 33) + 30, 250, 30, (chosenOne == i && chosenPage == page) ? &color3 : &color2);
            i += 1;
        }

        drawMenuElement("Choose", 20, (GetScreenWidth() >> 1), (GetScreenHeight() >> 1) + 200, 10, 10, &color2, page == chosenPage ? &color3 : &color2);
        drawMenuElement("Back", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 250, 10, 10, &color2, &color3);

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (page > 1) {
                if (isMouseInRange((GetScreenWidth() >> 1) - 100, (GetScreenHeight() >> 3), 10, 10, 20, "Previous")) {
                    page -= 1;
                    nextExists = GetMaps(maps, page + 1);
                    GetMaps(maps, page);
                }
            }
            if (nextExists) {
                if (isMouseInRange((GetScreenWidth() >> 1) + 80, (GetScreenHeight() >> 3), 10, 10, 20, "Next")) {
                    page += 1;
                    nextExists = GetMaps(maps, page + 1);
                    GetMaps(maps, page);
                }
            }

            i = 0;
            while (i < 10) {
                if (CheckCollisionPointRec(GetMousePosition(), getRectangle(GetScreenWidth() >> 1, (GetScreenHeight() >> 3) + ((i + 1) * 33) + 30, 250, 30))) {
                    chosenPage = page;
                    chosenOne = i;
                }

                i += 1;
            }

            if (page == chosenPage) 
            if (isMouseInRange((GetScreenWidth() >> 1), (GetScreenHeight() >> 1) + 200, 10, 10, 20, "Choose")) {
                if (chosenOne >= 0)
                if (maps[chosenOne].nr != 0) {
                    sprintf(mapName, "%s", maps[chosenOne].name);
                    *mapID = maps[chosenOne].id;
                    chosen = 1;
                }
            }
            if (isMouseInRange(GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 250, 10, 10, 20, "Back")) {
                chosen = 1;
            }
        }
    }
}

void createGame(enum state* state) {
    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };
    struct inputBox saveName = { .text = "\0", .length = 0, .coordinates = { GetScreenWidth() / 2.0f - 200, (float)(GetScreenHeight() >> 1) - 150, 400, 30 }, .frontSize = 20 };
    char errorMessage[512] = { 0 };
    char mapName[512] = "Map";
    int mapID = 0;
    int clicked = 0;
    extern struct gameInformations info;

    while (!WindowShouldClose() && *state == CREATE_NEW_GAME) {
        BeginDrawing();

        ClearBackground(color);

        drawMenuElement("Create Game", 20, GetScreenWidth() >> 1, GetScreenHeight() >> 3, 10, 10, &color2, &color2);

        drawMenuElement("Save Name", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) - 175, 10, 10, NULL, NULL);
        DrawInputBox(&saveName);
        drawMenuElement("Choose Map", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) - 105, 10, 10, NULL, NULL);
        drawMenuElement(mapName, 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) - 65, 10, 10, &color2, &color3);

        if (clicked == 1) drawTextWithBoxBehind(errorMessage, 20, (GetScreenWidth() >> 1), (GetScreenHeight() >> 1) + 70, 400, 40, &(Color) {.r = 255, .g = 255, .b = 255, .a = 255 });

        drawMenuElement("Create Game", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 150, 10, 10, &color2, &color3);
        drawMenuElement("Back", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 200, 10, 10, &color2, &color3);

        EndDrawing();

        updateInputBox(&saveName);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            clickAndChangeState(state, "Back", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 200, 10, 10, LOAD_GAME);

            if (isMouseInRange(GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 150, 10, 10, 20, "Create New Game")) {
                if (mapID == 0) {
                    sprintf(errorMessage, "Choose Map!");
                }
                else {
                    info.sessionID = createGameSession(saveName.text, info.owner, mapID, errorMessage);

                    if (*errorMessage == 0) {
                        sprintf(errorMessage, "Save Created Successfully!");
                        *state = GAME_SETUP;
                    }
                }

                clicked = 1;
            }

            if (isMouseInRange(GetScreenWidth() >> 1, (GetScreenHeight() >> 1) - 65, 10, 10, 20, mapName)) {
                chooseMap(mapName, &mapID);
            }
        }
    }
}