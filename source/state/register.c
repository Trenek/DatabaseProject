#include <stdio.h>

#include <raylib.h>

#include "state.h"
#include "inputBox.h"

#include "drawMenuElement.h"
#include "User.h"

void Register(enum state* state) {
    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };
    struct inputBox login = { .text = "\0", .length = 0, .coordinates = { GetScreenWidth() / 2.0f - 200, (float)(GetScreenHeight() >> 1) - 150, 400, 30 }, .frontSize = 20 };
    struct inputBox password = { .text = "\0", .length = 0, .coordinates = { GetScreenWidth() / 2.0f - 200, (float)(GetScreenHeight() >> 1) - 80, 400, 30 }, .frontSize = 20 };
    struct inputBox email = { .text = "\0", .length = 0, .coordinates = { GetScreenWidth() / 2.0f - 200, (float)(GetScreenHeight() >> 1) - 10, 400, 30 }, .frontSize = 20 };
    char errorMessage[512] = { 0 };
    int clicked = 0;

    while (!WindowShouldClose() && *state == REGISTER) {
        BeginDrawing();
        ClearBackground(color);

        drawMenuElement("Register", 20, GetScreenWidth() >> 1, GetScreenHeight() >> 3, 10, 10, &color2, &color2);
        drawMenuElement("Login", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) - 175, 10, 10, NULL, NULL);
        DrawInputBox(&login);
        drawMenuElement("Password", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) - 105, 10, 10, NULL, NULL);
        DrawInputBox(&password);
        drawMenuElement("Email", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) - 35, 10, 10, NULL, NULL);
        DrawInputBox(&email);
        drawMenuElement("Create Account", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 150, 10, 10, &color2, &color3);
        drawMenuElement("Back", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 200, 10, 10, &color2, &color3);

        if (clicked == 1) drawTextWithBoxBehind(errorMessage, 20, (GetScreenWidth() >> 1), (GetScreenHeight() >> 1) + 70, 550, 40, &(Color) { .r = 255, .g = 255, .b = 255, .a = 255 });

        EndDrawing();

        SetMouseCursor(checkCoursor(&login) || checkCoursor(&password) || checkCoursor(&email) ? MOUSE_CURSOR_IBEAM : MOUSE_CURSOR_DEFAULT);

        updateInputBox(&login);
        updateInputBox(&password);
        updateInputBox(&email);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseInRange(GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 150, 10, 10, 20, "Create Account")) {
                if (login.length == 0) {
                    sprintf(errorMessage, "Login cannot be empty");
                }
                else if (password.length == 0) {
                    sprintf(errorMessage, "Password cannot be empty");
                }
                else if (email.length == 0) {
                    sprintf(errorMessage, "Email cannot be empty");
                }
                else {
                    AddUser(errorMessage, login.text, password.text, email.text);

                    if (*errorMessage == 0) {
                        sprintf(errorMessage, "Registration ended with success");
                    }
                }

                clicked = 1;
            }
            clickAndChangeState(state, "Back", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 200, 10, 10, MENU);
        }
    }
}
