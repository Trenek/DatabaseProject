#include <stdlib.h>
#include <math.h>

#include "raylib.h"

#include "GridTileDef.h"
#include "GetProvinces.h"
#include "GetCivilizations.h"

struct GridTile** allocGridTile(int width, int height, Texture2D* texture) {
    struct GridTile** grid = malloc(width * sizeof(struct GridTile*));

    for (int x = 0; x < width; x++) {
        grid[x] = malloc(height * sizeof(struct GridTile));
    }

    GetProvinces(grid, texture, 1);

    return grid;
}

static bool check(Vector2 center, double radius, Camera2D camera) {
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

    return CheckCollisionPointPoly(mouse, array, 6);
}

void checkClick(int height, int width, int radius, struct GridTile** grid, Vector2* clicked, Camera2D camera) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            grid[x][y].isClicked = check(grid[x][y].screen_coordinates, radius, camera);
        }
    }
}

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

void DrawVisibleFields(double radius, int width, int height, struct GridTile** grid, Texture2D house) {
    float horiz = sqrtf(3) * radius / 2.0;
    float vert = radius;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            DrawTextureEx(*grid[x][y].texture, (Vector2) { .x = grid[x][y].screen_coordinates.x - horiz, .y = grid[x][y].screen_coordinates.y - vert }, 0, (radius * 2) / 2579.0, WHITE);

            if (grid[x][y].isClicked) {
                DrawPoly(grid[x][y].screen_coordinates, 6, radius, 90, (Color) { .r = 0, .g = 0, .b = 0, .a = 125 });
            }
        }
    }
};

void DrawCity(double radius, int width, int height, struct GridTile** grid, Texture2D* house) {
    float horiz = sqrtf(3) * radius / 2.0;
    float vert = radius;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (grid[x][y].CityID) {
                if (grid[x][y].isCapital) {
                    DrawTextureEx(house[1], (Vector2) { .x = grid[x][y].screen_coordinates.x - horiz, .y = grid[x][y].screen_coordinates.y - vert }, 0, (radius * 2) / 2579.0, (Color) { 255, 255, 255, 0xD2 });
                }
                else {
                    DrawTextureEx(house[0], (Vector2) { .x = grid[x][y].screen_coordinates.x - horiz, .y = grid[x][y].screen_coordinates.y - vert }, 0, (radius * 2) / 2579.0, (Color) { 255, 255, 255, 0xD2 });
                }
            }
        }
    }
};


void DrawPoliticalDivision(double radius, int width, int height, struct GridTile** grid, struct Civilization* civilizations) {
    float horiz = sqrtf(3) * radius / 2.0;
    float vert = radius;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            //DrawTextureEx(*grid[x][y].texture, (Vector2) { .x = grid[x][y].screen_coordinates.x - horiz, .y = grid[x][y].screen_coordinates.y - vert }, 0, (radius * 2) / 2579.0, WHITE);
            if (grid[x][y].civilizationID > 0)
            DrawPoly(grid[x][y].screen_coordinates, 6, radius, 90, civilizations[grid[x][y].civilizationNumber].color);
        }
    }
};

/**/

inline bool checkDrawLine(int x, int y, int incX, int incY, struct GridTile** grid) {
    bool result = false;

    if (x + incX > 0 && x + incX < 25) {
        if (y + incY > 0 && y + incY < 25) {
            if (grid[x][y].civilizationID != grid[x + incX][y + incY].civilizationID) {
                result = true;
            }
        }
    }

    return result;
}

void DrawPoliticalGridOutline(double radius, int width, int height, struct GridTile** grid) {
    float horiz = sqrtf(3) * radius / 2.0;
    float vert = radius / 2.0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (y % 2 == 1) {
                if (checkDrawLine(x, y, 0, -1, grid)) {
                    DrawLineEx((Vector2) { .x = grid[x][y].screen_coordinates.x - horiz, grid[x][y].screen_coordinates.y - vert }, (Vector2) { .x = grid[x][y].screen_coordinates.x, grid[x][y].screen_coordinates.y - radius }, 20, (Color) { 0, 0, 0, 255 });
                }
                if (checkDrawLine(x, y, 0, 1, grid)) {
                    DrawLineEx((Vector2) { .x = grid[x][y].screen_coordinates.x - horiz, grid[x][y].screen_coordinates.y + vert }, (Vector2) { .x = grid[x][y].screen_coordinates.x, grid[x][y].screen_coordinates.y + radius }, 20, (Color) { 0, 0, 0, 255 });
                }
                if (checkDrawLine(x, y, 1, 1, grid)) {
                    DrawLineEx((Vector2) { .x = grid[x][y].screen_coordinates.x + horiz, grid[x][y].screen_coordinates.y + vert }, (Vector2) { .x = grid[x][y].screen_coordinates.x, grid[x][y].screen_coordinates.y + radius }, 20, (Color) { 0, 0, 0, 255 });
                }
                if (checkDrawLine(x, y, 1, -1, grid)) {
                    DrawLineEx((Vector2) { .x = grid[x][y].screen_coordinates.x + horiz, grid[x][y].screen_coordinates.y - vert }, (Vector2) { .x = grid[x][y].screen_coordinates.x, grid[x][y].screen_coordinates.y - radius }, 20, (Color) { 0, 0, 0, 255 });
                }
            }
            else {
                if (checkDrawLine(x, y, -1, -1, grid)) {
                    DrawLineEx((Vector2) { .x = grid[x][y].screen_coordinates.x - horiz, grid[x][y].screen_coordinates.y - vert }, (Vector2) { .x = grid[x][y].screen_coordinates.x, grid[x][y].screen_coordinates.y - radius }, 20, (Color) { 0, 0, 0, 255 });
                }
                if (checkDrawLine(x, y, -1, 1, grid)) {
                    DrawLineEx((Vector2) { .x = grid[x][y].screen_coordinates.x - horiz, grid[x][y].screen_coordinates.y + vert }, (Vector2) { .x = grid[x][y].screen_coordinates.x, grid[x][y].screen_coordinates.y + radius }, 20, (Color) { 0, 0, 0, 255 });
                }
                if (checkDrawLine(x, y, 0, 1, grid)) {
                    DrawLineEx((Vector2) { .x = grid[x][y].screen_coordinates.x + horiz, grid[x][y].screen_coordinates.y + vert }, (Vector2) { .x = grid[x][y].screen_coordinates.x, grid[x][y].screen_coordinates.y + radius }, 20, (Color) { 0, 0, 0, 255 });
                }
                if (checkDrawLine(x, y, 0, -1, grid)) {
                    DrawLineEx((Vector2) { .x = grid[x][y].screen_coordinates.x + horiz, grid[x][y].screen_coordinates.y - vert }, (Vector2) { .x = grid[x][y].screen_coordinates.x, grid[x][y].screen_coordinates.y - radius }, 20, (Color) { 0, 0, 0, 255 });
                }
            }
            if (checkDrawLine(x, y, -1, 0, grid)) {
                DrawLineEx((Vector2) { .x = grid[x][y].screen_coordinates.x - horiz, grid[x][y].screen_coordinates.y + vert }, (Vector2) { .x = grid[x][y].screen_coordinates.x - horiz, grid[x][y].screen_coordinates.y - vert }, 20, (Color) { 0, 0, 0, 255 });
            }
            if (checkDrawLine(x, y, 1, 0, grid)) {
                DrawLineEx((Vector2) { .x = grid[x][y].screen_coordinates.x + horiz, grid[x][y].screen_coordinates.y + vert }, (Vector2) { .x = grid[x][y].screen_coordinates.x + horiz, grid[x][y].screen_coordinates.y - vert }, 20, (Color) { 0, 0, 0, 255 });
            }
        }
    }
};
/**/

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