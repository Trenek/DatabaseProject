#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "raylib.h"

#include "state.h"

#include "drawMenuElement.h"
#include "GetUsers.h"

void playerList(enum state* state) {
    Color color = { .a = 255, .b = 100, .r = 100, .g = 100 };
    Color color2 = { .a = 255, .b = 50, .g = 215, .r = 78 };
    Color color3 = { .a = 105, .b = 50, .g = 215, .r = 78 };
    struct player player[10];
    char buffer[128];
    int i = 0;
    int page = 1;
    int nextExists = 0;

    nextExists = GetUsers(player, page + 1);
    GetUsers(player, page);
    while (!WindowShouldClose() && *state == PLAYER_LIST) {
        BeginDrawing();
        ClearBackground((Color) { .r = 0, .g = 0, .b = 0, .a = 0 });
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), color);

        drawMenuElement("Player List", 20, GetScreenWidth() >> 1, GetScreenHeight() >> 3, 10, 10, &color2, &color2);

        i = 0;
        while (i < 10) {
            sprintf(buffer, player[i].id ? "%-3i.%-30s" : " ", player[i].id, player[i].name);
            drawTextWithBoxBehind(buffer, 15, GetScreenWidth() >> 1, (GetScreenHeight() >> 3) + ((i + 1) * 33) + 30, 250, 30, &color2);
            i += 1;
        }

        if (page > 1) drawMenuElement("Previous", 20, (GetScreenWidth() >> 1) - 100, (GetScreenHeight() >> 1) + 200, 10, 10, &color2, &color3);
        drawMenuElement("Back", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 200, 10, 10, &color2, &color3);
        if (nextExists) drawMenuElement("Next", 20, (GetScreenWidth() >> 1) + 80, (GetScreenHeight() >> 1) + 200, 10, 10, &color2, &color3);

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (page > 1) {
                if (isMouseInRange((GetScreenWidth() >> 1) - 100, (GetScreenHeight() >> 1) + 200, 10, 10, 20, "Previous")) {
                    page -= 1;
                    nextExists = GetUsers(player, page + 1);
                    GetUsers(player, page);
                }
            }
            if (nextExists) {
                if (isMouseInRange((GetScreenWidth() >> 1) + 80, (GetScreenHeight() >> 1) + 200, 10, 10, 20, "Next")) {
                    page += 1;
                    nextExists = GetUsers(player, page + 1);
                    GetUsers(player, page);
                }
            }


            clickAndChangeState(state, "Back", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 200, 10, 10, MENU);
        }
    }
}
