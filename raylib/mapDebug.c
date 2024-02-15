#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <raylib.h>

#include "state.h"
#include "GridTileDef.h"

#include "drawMenuElement.h"
#include "ProvinceTextures.h"
#include "GetCivilizations.h"
#include "GetPoliticalDivision.h"
#include "LoadingScreen.h"

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

void mapDebug(enum state* state) {
    const int width = 25;
    const int height = 25;
    int radius = 40;
    int frontSize = 40;
    Vector2 chosen = { 0, 0 };

    int size = 0;

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
                GenerateHexGrid(radius, width, height, grid);
                DrawVisibleFields(radius, width, height, grid, city);
                if (political) {
                    DrawPoliticalDivision(radius, width, height, grid, civilizations);
                    DrawCity(radius, width, height, grid, city);
                }
                //DrawClickedProvince(radius, width, height, grid);
                DrawClickedCivilization(radius, width, height, grid);
                DrawPoliticalGridOutline(radius, width, height, grid);
                DrawHexGridOutline(radius, width, height, grid);
                drawMenuElement("Choose Your Country Fellow Citizen", frontSize, (int)(sqrtf(3) * radius * width / 2.0), 0, 10, 10, NULL, NULL);
            EndMode2D();
        EndTextureMode();

        BeginDrawing();
        ClearBackground(BROWN);
        DrawTextureRec(screenCamera1.texture, splitScreenRect, (Vector2) { 0, 0 }, WHITE);

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
    }

    free(civilizations);
    UnloadRenderTexture(screenCamera1);
    UnloadTextures(texture, size);
    UnloadTexture(city[0]);
    UnloadTexture(city[1]);
}