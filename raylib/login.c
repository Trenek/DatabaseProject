#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "raylib.h"

#include "state.h"
#include "inputBox.h"

#include "drawMenuElement.h"
#include "logInQuery.h"

void login(enum state* state) {
    Color color = { .a = 255, .b = 100, .r = 100, .g = 100 };
    Color color2 = { .a = 255, .b = 50, .g = 215, .r = 78 };
    Color color3 = { .a = 105, .b = 50, .g = 215, .r = 78 };
    struct inputBox login = { .text = "\0", .length = 0, .coordinates = { GetScreenWidth() / 2.0f - 200, (float)(GetScreenHeight() >> 1) - 150, 400, 30 }, .frontSize = 20 };
    struct inputBox password = { .text = "\0", .length = 0, .coordinates = { GetScreenWidth() / 2.0f - 200, (float)(GetScreenHeight() >> 1) - 80, 400, 30 }, .frontSize = 20 };
    char buffor[512] = "";
    int clicked = 0;
    int tempLogin = 0;
    extern int loggedInID;
    
    while (!WindowShouldClose() && *state == LOGIN) {
        BeginDrawing();
        ClearBackground((Color) { .r = 0, .g = 0, .b = 0, .a = 0 });
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), color);

        drawMenuElement("Log In", 20, GetScreenWidth() >> 1, GetScreenHeight() >> 3, 10, 10, &color2, &color2);
        drawMenuElement("Login", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) - 175, 10, 10, NULL, NULL);
        DrawInputBox(&login);
        drawMenuElement("Password", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) - 105, 10, 10, NULL, NULL);
        DrawInputBox(&password);
        drawMenuElement("Login", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 150, 10, 10, &color2, &color3);
        drawMenuElement("Back", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 200, 10, 10, &color2, &color3);

        if (clicked == 1) drawTextWithBoxBehind(buffor, 20, (GetScreenWidth() >> 1), (GetScreenHeight() >> 1) + 70, 300, 40, &(Color) {.r = 255, .g = 255, .b = 255, .a = 255 });

        EndDrawing();

        SetMouseCursor(checkCoursor(&login) || checkCoursor(&password) ? MOUSE_CURSOR_IBEAM : MOUSE_CURSOR_DEFAULT);
        
        updateInputBox(&login);
        updateInputBox(&password);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            login.clicked = CheckCollisionPointRec(GetMousePosition(), login.coordinates);
            password.clicked = CheckCollisionPointRec(GetMousePosition(), password.coordinates);
            
            if (isMouseInRange(GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 150, 10, 10, 20, "Login")) {
                sprintf(buffor, "Logged Successfully");
                tempLogin = logInQuery(buffor, login.text, password.text);
                if (tempLogin != 0) {
                    loggedInID = tempLogin;
                }
                clicked = 1;
            }
            
            clickAndChangeState(state, "Back", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 200, 10, 10, MENU);
        }
        
    }
    
}
