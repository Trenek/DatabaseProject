#include <stdlib.h>
#include <math.h>

#include <raylib.h>

#include "GridTileDef.h"
#include "GetProvinces.h"
#include "GetCivilizations.h"

struct GridTile** allocMapGridTile(int width, int height, Texture2D* texture, int mapID) {
    struct GridTile** grid = malloc(width * sizeof(struct GridTile*));

    for (int x = 0; x < width; x++) {
        grid[x] = malloc(height * sizeof(struct GridTile));
    }

    GetProvinces(grid, texture, mapID);

    return grid;
}

struct GridTile** allocSessionGridTile(int width, int height, Texture2D* texture, int sessionID) {
    struct GridTile** grid = malloc(width * sizeof(struct GridTile*));

    for (int x = 0; x < width; x++) {
        grid[x] = malloc(height * sizeof(struct GridTile));
    }

    GetSessionProvinces(grid, texture, sessionID);

    return grid;
}

static bool check(Vector2 center, int radius, Camera2D camera) {
    Vector2 mouse = GetMousePosition();

    float horiz = sqrtf(3) * radius / 2.0f;
    float vert = radius / 2.0f;

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
    int x = 0;
    int y = 0;

    clicked->x = -1.0f;
    clicked->y = -1.0f;
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            grid[x][y].isClicked = check(grid[x][y].screen_coordinates, radius, camera);
            if (grid[x][y].isClicked) {
                clicked->x = (float)x;
                clicked->y = (float)y;
            }
        }
    }
}

void GenerateHexGrid(int radius, int width, int height, struct GridTile** grid) {
    float horiz = sqrtf(3) * radius;
    float vert = (3.0f / 2.0f) * radius;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            grid[x][y].screen_coordinates.x = (horiz * (x + ((y & 1) ? 0.5f : 0))) + 100;
            grid[x][y].screen_coordinates.y = (vert * y) + 100;
        }
    }
};

void DrawVisibleFields(int radius, int width, int height, struct GridTile** grid, Texture2D* house) {
    float horiz = sqrtf(3) * radius / 2.0f;
    int vert = radius;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            DrawTextureEx(*grid[x][y].texture, (Vector2) { .x = grid[x][y].screen_coordinates.x - horiz, .y = grid[x][y].screen_coordinates.y - vert }, 0, (radius * 2) / 2579.0f, WHITE);
            if (grid[x][y].CityID) {
                if (grid[x][y].isCapital) {
                    DrawTextureEx(house[1], (Vector2) { .x = grid[x][y].screen_coordinates.x - horiz, .y = grid[x][y].screen_coordinates.y - vert }, 0, (radius * 2) / 2579.0f, (Color) { 255, 255, 255, 255 });
                }
                else {
                    DrawTextureEx(house[0], (Vector2) { .x = grid[x][y].screen_coordinates.x - horiz, .y = grid[x][y].screen_coordinates.y - vert }, 0, (radius * 2) / 2579.0f, (Color) { 255, 255, 255, 255 });
                }
            }
        }
    }
};

void getClickedProvince(int width, int height, struct GridTile** grid, int* ptrX, int* ptrY) {
    int x = 0;
    int y = 0;

    while (y < height && !grid[x][y].isClicked) {
        x += 1;

        if (x == width) {
            x = 0;
            y += 1;
        }
    }

    *ptrX = x;
    *ptrY = y;
}

void DrawClickedProvince(int radius, int width, int height, struct GridTile** grid) {
    int x = 0;
    int y = 0;

    getClickedProvince(width, height, grid, &x, &y);
    DrawPoly(grid[x][y].screen_coordinates, 6, (float)radius, 90, (Color) { .r = 0, .g = 0, .b = 0, .a = 125 });
}

void DrawClickedCivilization(int radius, int width, int height, struct GridTile** grid) {
    int clickedX = 0;
    int clickedY = 0;

    getClickedProvince(width, height, grid, &clickedX, &clickedY);

    if (grid[clickedX][clickedY].civilizationID > 0) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (grid[clickedX][clickedY].civilizationID == grid[x][y].civilizationID) {
                    DrawPoly(grid[x][y].screen_coordinates, 6, (float)radius, 90, (Color) { .r = 0, .g = 0, .b = 0, .a = 125 });
                }
            }
        }
    }
    else {
        DrawPoly(grid[clickedX][clickedY].screen_coordinates, 6, (float)radius, 90, (Color) { .r = 0, .g = 0, .b = 0, .a = 125 });
    }
}

void DrawCity(int radius, int width, int height, struct GridTile** grid, Texture2D* house) {
    float horiz = sqrtf(3) * radius / 2.0f;
    int vert = radius;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (grid[x][y].CityID) {
                if (grid[x][y].isCapital) {
                    DrawTextureEx(house[1], (Vector2) { .x = grid[x][y].screen_coordinates.x - horiz, .y = grid[x][y].screen_coordinates.y - vert }, 0, (radius * 2) / 2579.0f, (Color) { 255, 255, 255, 0xD2 });
                }
                else {
                    DrawTextureEx(house[0], (Vector2) { .x = grid[x][y].screen_coordinates.x - horiz, .y = grid[x][y].screen_coordinates.y - vert }, 0, (radius * 2) / 2579.0f, (Color) { 255, 255, 255, 0xD2 });
                }
            }
        }
    }
};


void DrawPoliticalDivision(int radius, int width, int height, struct GridTile** grid, struct Civilization* civilizations) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (grid[x][y].civilizationID > 0)
            DrawPoly(grid[x][y].screen_coordinates, 6, (float)radius, 90, civilizations[grid[x][y].civilizationNumber].color);
        }
    }
};

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

void DrawPoliticalGridOutline(int radius, int width, int height, struct GridTile** grid) {
    float horiz = sqrtf(3) * radius / 2.0f;
    float vert = radius / 2.0f;

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

void DEBUG_DrawCoordinatesOnHexGrid(int radius, int width, int height, struct GridTile** grid) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            DrawText(TextFormat("y: %d", y), (int)(grid[x][y].screen_coordinates.x - (radius / 2.0)), (int)grid[x][y].screen_coordinates.y, radius >> 1, LIME);
            DrawText(TextFormat("x: %d", x), (int)(grid[x][y].screen_coordinates.x - (radius / 2.0)), (int)(grid[x][y].screen_coordinates.y - (radius / 2.0)), radius >> 1, VIOLET);
        }
    }
};

void DrawHexGridOutline(int radius, int width, int height, struct GridTile** grid) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            DrawPolyLines(grid[x][y].screen_coordinates, 6, (float)radius, 90,
                //BROWN
                BLACK
            );
        }
    }
};