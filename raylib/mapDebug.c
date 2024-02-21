#include <stdlib.h>
#include <stdio.h>

#include <raylib.h>

#include "state.h"
#include "GridTileDef.h"

#include "drawMenuElement.h"
#include "ProvinceTextures.h"
#include "GetCivilizations.h"
#include "GetPoliticalDivision.h"
#include "LoadingScreen.h"
#include "createCamera.h"
#include "getDimensions.h"
#include "modifyBackgroundColor.h"

void mapDebug(enum state* state) {
    int width = 0;
    int height = 0;
    int radius = 40;
    int frontSize = 40;
    Vector2 chosen = { 0, 0 };
    //Color color = { 100, 100, 100, 255 };
    //Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    //Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };
    int size = 0;

    GetMapDimensions(&width, &height, 1);

    Camera2D camera1 = createCamera(width, height, radius);

    RenderTexture screenCamera1 = LoadRenderTexture(GetScreenWidth(), GetScreenHeight() + 20);
    Rectangle splitScreenRect = { 0.0f, 0.0f, (float)screenCamera1.texture.width, (float)-screenCamera1.texture.height };

    Texture2D* texture = LoadTextures(&size);
    Texture2D city[2];

    struct GridTile** grid = allocMapGridTile(width, height, texture, 1);

    struct Civilization* civilizations = GetCivilizations(1);

    bool political = true;

    addCityTexture(city, size);

    GetPoliticalDivision(grid, 1);

    while (!WindowShouldClose() && *state == MAP_DEBUG) {
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
                //DrawTextureRec(screenCamera1.texture, splitScreenRect, (Vector2) { 0, 0 }, WHITE);
                GenerateHexGrid(radius, width, height, grid);
                DrawVisibleFields(radius, width, height, grid, city);
                if (political) {
                    DrawPoliticalDivision(radius, width, height, grid, civilizations);
                    DrawCity(radius, width, height, grid, city);
                }
                DrawClickedCivilization(radius, width, height, grid);
                DrawNormalPoliticalGridOutline(radius, width, height, grid, -1, BLACK);
                DrawHexGridOutline(radius, width, height, grid);
                drawMenuElement("Choose Your Country Fellow Citizen", frontSize, (int)(sqrtf(3) * radius * width / 2.0), 0, 10, 10, NULL, NULL);
            EndMode2D();
        EndTextureMode();




        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            checkClick(height, width, radius, grid, &chosen, camera1);
        }

        if (IsKeyPressed(KEY_P)) {
            Pause(state, MAP_DEBUG, &screenCamera1, &splitScreenRect);
        }

        if (IsKeyPressed(KEY_M)) {
            political = !political;
        }
        //clickAndChangeState(state, "Back", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 200, 10, 10, MENU);
    }

    free(civilizations);
    UnloadRenderTexture(screenCamera1);
    UnloadTextures(texture, size);
    UnloadTexture(city[0]);
    UnloadTexture(city[1]);

}