#include <stdio.h>
#include <string.h>

#include <raylib.h>

#include "state.h"
#include "inputBox.h"
#include "gameInformations.h"

#include "drawMenuElement.h"
#include "logInQuery.h"

void login(enum state* state) {
    extern struct gameInformations info;

    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };
    struct inputBox login = { .text = "\0", .length = 0, .coordinates = { GetScreenWidth() / 2.0f - 200, (float)(GetScreenHeight() >> 1) - 150, 400, 30 }, .frontSize = 20 };
    struct inputBox password = { .text = "\0", .length = 0, .coordinates = { GetScreenWidth() / 2.0f - 200, (float)(GetScreenHeight() >> 1) - 80, 400, 30 }, .frontSize = 20 };
    int clicked = 0;
    int tempLogin = 0;

    char errorMessage[512] = { 0 };
    
    while (!WindowShouldClose() && *state == LOGIN) {
        BeginDrawing();
        ClearBackground(color);

        drawMenuElement("Log In", 20, GetScreenWidth() >> 1, GetScreenHeight() >> 3, 10, 10, &color2, &color2);
        drawMenuElement("Login", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) - 175, 10, 10, NULL, NULL);
        DrawInputBox(&login);
        drawMenuElement("Password", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) - 105, 10, 10, NULL, NULL);
        DrawInputBox(&password);
        drawMenuElement("Login", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 150, 10, 10, &color2, &color3);
        drawMenuElement("Back", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 200, 10, 10, &color2, &color3);

        if (clicked == 1) drawTextWithBoxBehind(errorMessage, 20, (GetScreenWidth() >> 1), (GetScreenHeight() >> 1) + 70, 300, 40, &(Color) {.r = 255, .g = 255, .b = 255, .a = 255 });

        EndDrawing();

        SetMouseCursor(checkCoursor(&login) || checkCoursor(&password) ? MOUSE_CURSOR_IBEAM : MOUSE_CURSOR_DEFAULT);
        
        updateInputBox(&login);
        updateInputBox(&password);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {            
            if (isMouseInRange(GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 150, 10, 10, 20, "Login")) {
                tempLogin = logInQuery(errorMessage, login.text, password.text);

                if (*errorMessage == 0) {
                    strcat(errorMessage, "Logged Successfully");
                    info.owner = tempLogin;
                }

                clicked = 1;
            }
            
            clickAndChangeState(state, "Back", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 200, 10, 10, MENU);
        }
        
    }
    
}
