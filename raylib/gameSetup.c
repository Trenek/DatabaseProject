#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <raylib.h>

#include "state.h"
#include "gameInformations.h"
#include "GridTileDef.h"

#include "drawMenuElement.h"
#include "ShowPlayer.h"
#include "inputBox.h"
#include "ProvinceTextures.h"
#include "LoadingScreen.h"

#include "logInQuery.h"
#include "AddUser.h"
#include "AddPlayer.h"
#include "GetCivilizations.h"
#include "GetPoliticalDivision.h"
#include "AssignCivilization.h"

inline void addCityTexture(Texture2D* city, int size) {
    Image image;

    LoadingScreen(size, size + 2);
    image = LoadImage("assets/City.png");
    city[0] = LoadTextureFromImage(image);
    UnloadImage(image);
    LoadingScreen(size + 1, size + 2);
    image = LoadImage("assets/CapitalCity.png");
    city[1] = LoadTextureFromImage(image);
    LoadingScreen(size + 2, size + 2);
    UnloadImage(image);
}

inline Camera2D createCamera(int width, int height, int radius) {
    float one = GetScreenWidth() / ((sqrtf(3) * radius) * (width + 3));
    float two = GetScreenHeight() / ((3 * radius * (height + 3)) / 2.0f);

    return (Camera2D) {
        .target = (Vector2){ 950, 800 },
        .offset = (Vector2){ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f },
        .rotation = 0.0f,
        .zoom = two > one ? one : two
    };
}

static void chooseCivilization(int playerID, Texture2D* texture, Texture2D* city) {
    extern struct gameInformations info;

    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };
    int width = 25;
    int height = 25;
    int radius = 40;
    int frontSize = 40;
    Vector2 chosen = { -1, -1 };

    Camera2D camera1 = createCamera(width, height, radius);

    RenderTexture screenCamera1 = LoadRenderTexture(GetScreenWidth(), GetScreenHeight() + 20);
    Rectangle splitScreenRect = { 0.0f, 0.0f, (float)screenCamera1.texture.width, (float)-screenCamera1.texture.height };

    struct GridTile** grid = allocSessionGridTile(width, height, texture, info.sessionID);

    struct Civilization* civilizations = GetSessionCivilizations(info.sessionID);

    bool political = true;

    GetSessionPoliticalDivision(grid, info.sessionID);

    int exit = 0;
    char errorMessage[512] = { 0 };
    int error = 0;

    while (!WindowShouldClose() && !exit) {
        if (IsKeyDown(KEY_A)) camera1.offset.x += 1 / camera1.zoom;
        if (IsKeyDown(KEY_D)) camera1.offset.x -= 1 / camera1.zoom;
        if (IsKeyDown(KEY_S)) camera1.offset.y -= 1 / camera1.zoom;
        if (IsKeyDown(KEY_W)) camera1.offset.y += 1 / camera1.zoom;

        if (IsKeyDown(KEY_LEFT)) camera1.target.x -= 1 / camera1.zoom;
        if (IsKeyDown(KEY_RIGHT)) camera1.target.x += 1 / camera1.zoom;
        if (IsKeyDown(KEY_DOWN)) camera1.target.y += 1 / camera1.zoom;
        if (IsKeyDown(KEY_UP)) camera1.target.y -= 1 / camera1.zoom;

        if (IsKeyDown(KEY_Q)) camera1.zoom += 0.01f;
        if (IsKeyDown(KEY_E)) camera1.zoom -= 0.01f;
        camera1.zoom += (GetMouseWheelMove() * camera1.zoom / 16);
        if (camera1.zoom < 0.1) camera1.zoom = 0.1f;
        if (camera1.zoom > 10) camera1.zoom = 10.0f;

        BeginTextureMode(screenCamera1);
            ClearBackground(BROWN);

            BeginMode2D(camera1);
                GenerateHexGrid(radius, width, height, grid);
                DrawVisibleFields(radius, width, height, grid, city);
                if (political) {
                    DrawPoliticalDivision(radius, width, height, grid, civilizations);
                    DrawCity(radius, width, height, grid, city);
                }
                DrawClickedCivilization(radius, width, height, grid);
                DrawPoliticalGridOutline(radius, width, height, grid);
                DrawHexGridOutline(radius, width, height, grid);
                drawMenuElement("Choose Your Country Fellow Citizen", frontSize, (int)(sqrtf(3) * radius * width / 2.0), 0, 10, 10, NULL, NULL);
            EndMode2D();

            if (chosen.x != -1.0f) {
                if (grid[(int)chosen.x][(int)chosen.y].civilizationID > 0) {
                    DrawRectangle(0, GetScreenHeight() - 240, GetScreenWidth() / 2, 240, (Color) { .r = 0, .g = 0, .b = 0, .a = 255 });
                    DrawText("Civilization", (GetScreenWidth() / 4) - (MeasureText("Civilization", 20) / 2), GetScreenHeight() - 190, 20, (Color) { .r = 255, .g = 255, .b = 255, .a = 255 });
                    DrawText(civilizations[grid[(int)chosen.x][(int)chosen.y].civilizationNumber].name, (GetScreenWidth() / 4) - (MeasureText(civilizations[grid[(int)chosen.x][(int)chosen.y].civilizationNumber].name, 20) / 2), GetScreenHeight() - 140, 20, (Color) { .r = 255, .g = 255, .b = 255, .a = 255 });
                    if (error == 1) drawTextWithBoxBehind(errorMessage, 20, GetScreenWidth() / 4, GetScreenHeight() - 90, 400, 40, &(Color) {.r = 255, .g = 255, .b = 255, .a = 255 });

                    drawMenuElement("Choose", 20, GetScreenWidth() / 4, GetScreenHeight() - 40, 10, 10, &color2, &color3);
                }
            }
            drawMenuElement("Back", 20, (3 * GetScreenWidth() / 4) + 100, GetScreenHeight() - 40, 10, 10, &color2, &color3);

        EndTextureMode();

        BeginDrawing();

        ClearBackground(BROWN);
        DrawTextureRec(screenCamera1.texture, splitScreenRect, (Vector2) { 0, 0 }, WHITE);

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (chosen.x != -1.0f && grid[(int)chosen.x][(int)chosen.y].civilizationID > 0 && CheckCollisionPointRec(GetMousePosition(), (Rectangle){ 0, GetScreenHeight() / 2.0f, GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f })) {
                if (isMouseInRange(GetScreenWidth() / 4, GetScreenHeight() - 40, 10, 10, 20, "Choose")) {
                    *errorMessage = 0;
                    AssignCivilization(errorMessage, playerID, grid[(int)chosen.x][(int)chosen.y].civilizationID, info.sessionID);

                    if (*errorMessage == 0) {
                        exit = 1;
                    }
                    else {
                        error = 1;
                    }
                }
            }

            else if (isMouseInRange((3 * GetScreenWidth() / 4) + 100, GetScreenHeight() - 40, 10, 10, 20, "Back")) {
                exit = 1;
            }
            else {
                checkClick(height, width, radius, grid, &chosen, camera1);
            }
        }

        if (IsKeyPressed(KEY_M)) {
            political = !political;
        }
    }

    free(civilizations);
    UnloadRenderTexture(screenCamera1);
}

static int addPlayer(void) {
    int exit = 0;
    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };
    int page = 1;
    int nextExists = 0;
    char playerName[256] = "Lubiê Placki :>";
    char civilizationName[256] = "Civilization";
    int playerID = 0;
    int playerNr = 0;
    struct inputBox login = {
        .clicked = 0,
        .coordinates = (Rectangle) { (GetScreenWidth() >> 1) - 200.0f, (GetScreenHeight() >> 1) - 100.0f, 400, 30 },
        .frontSize = 20,
        .length = 0,
        .text = ""
    };
    struct inputBox password = {
        .clicked = 0,
        .coordinates = (Rectangle) { (GetScreenWidth() >> 1) - 200.0f, (GetScreenHeight() >> 1) - 10.0f, 400, 30 },
        .frontSize = 20,
        .length = 0,
        .text = ""
    };
    struct inputBox email = {
        .clicked = 0,
        .coordinates = (Rectangle) { (GetScreenWidth() >> 1) - 200.0f, (GetScreenHeight() >> 1) + 90.0f, 400, 30 },
        .frontSize = 20,
        .length = 0,
        .text = ""
    };
    extern struct gameInformations info;

    int state = 0; // 0 - login, 1 - register
    char errorMessage[512] = { 0 };
    int clicked = 0;
    int success = 0;
    int ID = 0;

    nextExists = ShowPlayer(playerName, civilizationName, &playerID, info.sessionID, page + 1);
    playerNr = ShowPlayer(playerName, civilizationName, &playerID, info.sessionID, page);
    while (!WindowShouldClose() && !exit) {
        BeginDrawing();

        ClearBackground(color);

        drawMenuElement(state == 0 ? "Login" : "Register", 20, GetScreenWidth() >> 1, GetScreenHeight() >> 3, 10, 10, &color2, &color2);
        drawMenuElement(state == 0 ? "Login" : "Register", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 150, 10, 10, &color2, &color3);
        drawMenuElement("Back", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 200, 10, 10, &color2, &color3);
        drawMenuElement(state == 0 ? "Register" : "Login", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 250, 10, 10, &color2, &color3);
        drawMenuElement("Login", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) - 150, 10, 10, &color2, &color2);
        DrawInputBox(&login);
        drawMenuElement("Password", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) - 50, 10, 10, &color2, &color2);
        DrawInputBox(&password);
        if (state == 1) {
            drawMenuElement("Email", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 50, 10, 10, &color2, &color2);
            DrawInputBox(&email);
        }
        if (clicked == 1) {
            drawTextWithBoxBehind(errorMessage, 20, (GetScreenWidth() >> 1), 20, 300, 40, &(Color) {.r = 255, .g = 255, .b = 255, .a = 255 });
        }

        EndDrawing();

        updateInputBox(&login);
        updateInputBox(&password);
        updateInputBox(&email);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            switch (state) {
                case 0:
                    if (isMouseInRange((GetScreenWidth() >> 1), (GetScreenHeight() >> 1) + 150, 10, 10, 20, "Login")) {
                        if (login.length == 0) {
                            sprintf(errorMessage, "Login is empty");
                        }
                        else if (password.length == 0) {
                            sprintf(errorMessage, "Password is empty");
                        }
                        else {
                            *errorMessage = 0;
                            ID = logInQuery(errorMessage, login.text, password.text);

                            if (ID != 0) {
                                AddPlayer(errorMessage, info.sessionID, ID);

                                if (*errorMessage == 0) {
                                    success = 1;
                                    exit = 1;
                                }
                            }
                        }    
                        clicked = 1;
                    }
                    break;
                case 1:
                    if (isMouseInRange((GetScreenWidth() >> 1), (GetScreenHeight() >> 1) + 150, 10, 10, 20, "Register")) {
                        if (login.length == 0) {
                            sprintf(errorMessage, "Login is empty");
                        }
                        else if (password.length == 0) {
                            sprintf(errorMessage, "Password is empty");
                        }
                        else if (email.length == 0) {
                            sprintf(errorMessage, "Email is empty");
                        }
                        else {
                            *errorMessage = 0;
                            AddUser(errorMessage, login.text, password.text, email.text);

                            if (*errorMessage == 0) {
                                ID = logInQuery(errorMessage, login.text, password.text);

                                if (ID != 0) {
                                    AddPlayer(errorMessage, info.sessionID, ID);
                                    
                                    if (*errorMessage == 0) {
                                        success = 1;
                                        exit = 1;
                                    }
                                }
                            }
                        }
                        clicked = 1;
                    }
                    break;
            }

            if (isMouseInRange(GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 200, 10, 10, 20, "Back")) {
                exit = 1;
            }

            if (isMouseInRange(GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 250, 10, 10, 20, state == 0 ? "Register" : "Login")) {
                state = state == 1 ? 0 : 1;
            }
        }
    }

    return success;
}

void gameSetup(enum state* state) {
    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };
    int page = 1;
    int nextExists = 0;
    char playerName[256] = "Nikt";
    char civilizationName[256] = "Civilization";
    int playerID = 0;
    int playerNr = 0;
    extern struct gameInformations info;
    int size = 0;
    Texture2D* texture = LoadTextures(&size);
    Texture2D city[2];
    int reload = 1;

    addCityTexture(city, size);

    while (!WindowShouldClose() && *state == GAME_SETUP) {
        if (reload == 1) {
            nextExists = ShowPlayer(playerName, civilizationName, &playerID, info.sessionID, page + 1);
            strcpy(civilizationName, "Civilization");
            playerNr = ShowPlayer(playerName, civilizationName, &playerID, info.sessionID, page);
            reload = 0;
        }

        BeginDrawing();

        ClearBackground(color);

        drawMenuElement("Game Setup", 20, GetScreenWidth() >> 1, GetScreenHeight() >> 3, 10, 10, &color2, &color2);
        drawMenuElement("Back", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 200, 10, 10, &color2, &color3);
        drawMenuElement("Player", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) - 150, 10, 10, &color2, &color2);
        drawMenuElement(nextExists > 0 ? "Next" : "Add", 20, (GetScreenWidth() >> 1) + 90, (GetScreenHeight() >> 1) - 150, 10, 10, &color2, &color3);
        if (page > 1) drawMenuElement("Previous", 20, (GetScreenWidth() >> 1) - 110, (GetScreenHeight() >> 1) - 150, 10, 10, &color2, &color3);
        drawMenuElement(playerName, 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) - 90, 10, 10, &color2, &color2);
        drawMenuElement(civilizationName, 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) - 40, 10, 10, &color2, &color3);

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            clickAndChangeState(state, "Create New Game", 20, (GetScreenWidth() >> 1) - 100, (GetScreenHeight() >> 1) + 150, 10, 10, CREATE_NEW_GAME);
            clickAndChangeState(state, "Back", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 200, 10, 10, LOAD_GAME);

            if (nextExists > 0) {
                if (isMouseInRange((GetScreenWidth() >> 1) + 90, (GetScreenHeight() >> 1) - 150, 10, 10, 20, "Next")) {
                    page += 1;
                    reload = 1;
                }
            }
            else {
                if (isMouseInRange((GetScreenWidth() >> 1) + 90, (GetScreenHeight() >> 1) - 150, 10, 10, 20, "Add")) {
                    if (addPlayer()) {
                        page += 1;
                        reload = 1;
                    }
                }
            }
            if (page > 1)
            if (isMouseInRange((GetScreenWidth() >> 1) - 110, (GetScreenHeight() >> 1) - 150, 10, 10, 20, "Previous")) {
                page -= 1;
                reload = 1;
            }

            if (isMouseInRange(GetScreenWidth() >> 1, (GetScreenHeight() >> 1) - 40, 10, 10, 20, civilizationName)) {
                chooseCivilization(playerID, texture, city);
                reload = 1;
            }
        }
    }

    UnloadTextures(texture, size);
    UnloadTexture(city[0]);
    UnloadTexture(city[1]);
}