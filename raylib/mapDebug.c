#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "raylib.h"

#include "state.h"
#include "position.h"

#include "drawMenuElement.h"

static void Pause(enum state* state) {
    Color color1 = { .r = 100, .g = 100, .b = 100, .a = 200 };
    Color color2 = { .r = 0, .g = 0, .b = 0, .a = 255 };

    *state = PAUSE;
    do {
        BeginDrawing();

        ClearBackground(color1);

        drawMenuElement("Paused", 40, GetScreenWidth() >> 1, GetScreenHeight() >> 1, 10, 10, NULL, NULL);

        drawMenuElement("Resume", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 80, 10, 10, NULL, &color2);
        drawMenuElement("Exit to Menu", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 130, 10, 10, NULL, &color2);
        drawMenuElement("Exit", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 180, 10, 10, NULL, &color2);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            clickAndChangeState(state, "Resume", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 80, 10, 10, MAP_DEBUG);
            clickAndChangeState(state, "Exit to Menu", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 130, 10, 10, MENU);
            clickAndChangeState(state, "Exit", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 180, 10, 10, EXIT);
        }
        if (IsKeyPressed(KEY_P)) {
            *state = MAP_DEBUG;
        }
    } while (*state == PAUSE && !WindowShouldClose());
}

#include <stdlib.h>
#include <math.h>

#include "raylib.h"

struct GridTile {
    Vector2 screen_coordinates;
    Color color;
    Texture2D* texture;
    bool isClicked;
};

void GenerateHexGrid(int radius, int width, int height, struct GridTile** grid) {
    float horiz = sqrtf(3) * radius;
    float vert = (3.0 / 2.0) * radius;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            grid[x][y].screen_coordinates.x = (horiz * (x + ((y & 1) ? 0.5 : 0))) + 100;
            grid[x][y].screen_coordinates.y = (vert * y) + 100;
        }
    }
};

void DrawVisibleFields(double radius, int width, int height, struct GridTile** grid) {
    float horiz = sqrtf(3) * radius / 2.0;
    float vert = radius;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            DrawTextureEx(*grid[x][y].texture, (Vector2) { .x = grid[x][y].screen_coordinates.x - horiz, .y = grid[x][y].screen_coordinates.y - vert }, 0, (radius * 2) / 2579.0, WHITE);
            if (grid[x][y].isClicked) {
                DrawPoly(grid[x][y].screen_coordinates, 6, radius, 90, (Color) {.r = 0, .g = 0, .b = 0, .a = 125});
            }
        }
    }
};

void DEBUG_DrawCoordinatesOnHexGrid(double radius, int width, int height, struct GridTile** grid) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            DrawText(TextFormat("y: %d", y), grid[x][y].screen_coordinates.x - (radius / 2), grid[x][y].screen_coordinates.y, radius / 2, LIME);
            DrawText(TextFormat("x: %d", x), grid[x][y].screen_coordinates.x - (radius / 2), grid[x][y].screen_coordinates.y - (radius / 2), radius / 2, VIOLET);
        }
    }
};

void DrawHexGridOutline(double radius, int width, int height, struct GridTile** grid) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            DrawPolyLines(grid[x][y].screen_coordinates, 6, radius, 90,
                //BROWN
                BLACK
            );
        }
    }
};

bool CheckCollisionPointPoly2(Vector2 point, Vector2* points, int pointCount) {
    bool inside = false;

    if (pointCount > 2) {
        for (int i = 0, j = pointCount - 1; i < pointCount; j = i++) {
            if ((points[i].y > point.y) != (points[j].y > point.y) &&
                (point.x < (points[j].x - points[i].x) * (point.y - points[i].y) / (points[j].y - points[i].y) + points[i].x)) {
                inside = !inside;
            }
        }
    }

    return inside;
}

bool check(Vector2 center, double radius, Camera2D camera) {
    Vector2 mouse = GetMousePosition();

    float horiz = sqrtf(3) * radius / 2.0;
    float vert = radius / 2.0;

    mouse.x -= camera.offset.x;
    mouse.y -= camera.offset.y;

    mouse.x /= camera.zoom;
    mouse.y /= camera.zoom;

    mouse.x += camera.target.x;
    mouse.y += camera.target.y;

    Vector2 array[6] = {
        [0] = (Vector2) {.x = center.x, .y = center.y - radius},
        [1] = (Vector2) {.x = center.x + horiz, .y = center.y - vert},
        [2] = (Vector2) {.x = center.x + horiz, .y = center.y + vert},
        [3] = (Vector2) {.x = center.x, .y = center.y + radius},
        [4] = (Vector2) {.x = center.x - horiz, .y = center.y + vert},
        [5] = (Vector2) {.x = center.x - horiz, .y = center.y - vert},
    };

    return CheckCollisionPointPoly2(mouse, array, 6);
}

void checkClick(int height, int width, int radius, struct GridTile** grid, Vector2* clicked, Camera2D camera) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            grid[x][y].isClicked = check(grid[x][y].screen_coordinates, radius, camera);
        }
    }
}

struct GridTile** allocGridTile(int width, int height, Texture2D* texture) {
    struct GridTile** grid = malloc(width * sizeof(struct GridTile*));

    for (int x = 0; x < width; x++) {
        grid[x] = malloc(height * sizeof(struct GridTile));
    }

    for (int x = 0; x < width; x += 1) {
        for (int y = 0; y < height; y += 1) {
            grid[x][y].color = BEIGE;
            grid[x][y].texture = texture;
        }
    }

    return grid;
}

static void drawSomething(double radius, int width, int height, struct GridTile** grid) {
    GenerateHexGrid(radius, width, height, grid);
    DrawVisibleFields(radius, width, height, grid);
    DrawHexGridOutline(radius, width, height, grid);
    //DEBUG_DrawCoordinatesOnHexGrid(radius, width, height, grid);
}

void mapDebug(enum state* state) {
    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    const int width = 25;
    const int height = 25;
    int radius = 40;
    int frontSize = 40;
    Vector2 chosen = { 0, 0 };

    float one = GetScreenWidth() / ((sqrtf(3) * radius) * (width + 3));
    float two = GetScreenHeight() / ((3.0 * radius / 2.0) * (float)(height + 3));

    Camera2D camera1 = {
        .target = (Vector2){ 950, 800 },
        .offset = (Vector2){ GetScreenWidth() / 2, GetScreenHeight() / 2},
        .rotation = 0.0f,
        .zoom = two > one ? one : two
    };

    float horiz = sqrtf(3) * radius / 2.0;
    float vert = radius;

    RenderTexture screenCamera1 = LoadRenderTexture(GetScreenWidth(), GetScreenHeight() + 20);
    Rectangle splitScreenRect = { 0.0f, 0.0f, (float)screenCamera1.texture.width, (float)-screenCamera1.texture.height };

    Image image = LoadImage("assets/FlatTerrain.png");
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);

    struct GridTile** grid = allocGridTile(width, height, &texture);

    while (!WindowShouldClose() && *state == MAP_DEBUG) {
        if (IsKeyDown(KEY_A)) camera1.offset.x += 1 / camera1.zoom;
        if (IsKeyDown(KEY_D)) camera1.offset.x -= 1 / camera1.zoom;
        if (IsKeyDown(KEY_S)) camera1.offset.y -= 1 / camera1.zoom;
        if (IsKeyDown(KEY_W)) camera1.offset.y += 1 / camera1.zoom;

        if (IsKeyDown(KEY_LEFT)) camera1.target.x -= 1 / camera1.zoom;
        if (IsKeyDown(KEY_RIGHT)) camera1.target.x += 1 / camera1.zoom;
        if (IsKeyDown(KEY_DOWN)) camera1.target.y += 1 / camera1.zoom;
        if (IsKeyDown(KEY_UP)) camera1.target.y -= 1 / camera1.zoom;

        if (IsKeyDown(KEY_Q)) camera1.zoom += 0.01;
        if (IsKeyDown(KEY_E)) camera1.zoom -= 0.01;
        camera1.zoom += GetMouseWheelMove() / 16;

        BeginTextureMode(screenCamera1);
            ClearBackground(BROWN);

            BeginMode2D(camera1);
                drawSomething(radius, width, height, grid);
                drawMenuElement("Choose Your Country Fellow Citizen", frontSize, sqrtf(3) * radius * width / 2,  0, 10, 10, NULL, NULL);
                //DrawTexture(texture, GetScreenWidth() / 2 - texture.width / 2, GetScreenHeight() / 2 - texture.height / 2, WHITE);
                //DrawTextureEx(texture, (Vector2) { .x = 100 - horiz, .y = 100 - vert }, 0, (radius << 1) / 2579.0, WHITE);
            EndMode2D();
        EndTextureMode();

        BeginDrawing();
        ClearBackground(BROWN);
        DrawTextureRec(screenCamera1.texture, splitScreenRect, (Vector2) { 0, 0 }, WHITE);
        //DrawText(TextFormat("%f %f %f %f %f", camera1.offset.x, camera1.offset.y, camera1.target.x, camera1.target.y, camera1.zoom), 0, 0, 20, (Color) { .r = 0, .g = 0, .b = 0, .a = 255 });

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            checkClick(height, width, radius, grid, &chosen, camera1);
        }

        if (IsKeyPressed(KEY_P)) {
            Pause(state);
        }
    }

    UnloadRenderTexture(screenCamera1); // Unload render texture
    UnloadTexture(texture);
}