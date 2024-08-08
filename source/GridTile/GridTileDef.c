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
                DrawTextureEx(
                    grid[x][y].isCapital ? house[1] : house[0], 
                    (Vector2) { .x = grid[x][y].screen_coordinates.x - horiz, .y = grid[x][y].screen_coordinates.y - vert }, 
                    0, 
                    (radius * 2) / 2579.0f, 
                    WHITE
                );
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
                DrawTextureEx(
                    grid[x][y].isCapital ? house[1] : house[0], 
                    (Vector2) { .x = grid[x][y].screen_coordinates.x - horiz, .y = grid[x][y].screen_coordinates.y - vert },
                    0, 
                    (radius * 2) / 2579.0f, 
                    (Color) { 255, 255, 255, 0xD2 }
                );
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

inline bool checkDrawLine(int x, int y, int incX, int incY, struct GridTile** grid, int chosenID, int* isChosen, int playerID, int* isPlayer) {
    bool result = false;

    if (x + incX > 0 && x + incX < 25) {
        if (y + incY > 0 && y + incY < 25) {
            if (grid[x][y].civilizationID != grid[x + incX][y + incY].civilizationID) {
                result = true;
            }
            if (isChosen != NULL) *isChosen = (grid[x][y].civilizationID == chosenID) || (grid[x + incX][y + incY].civilizationID == chosenID);
            if (isPlayer != NULL) *isPlayer = (grid[x][y].civilizationID == playerID) || (grid[x + incX][y + incY].civilizationID == playerID);
        }
    }

    return result;
}

void DrawNormalPoliticalGridOutline(int radius, int width, int height, struct GridTile** grid, int playerID, Color playerColor) {
    int isChosen = 0;
    int isPlayer = 0;
#define THICKNESS 20

    float horiz = sqrtf(3) * radius / 2.0f;
    float vert = radius / 2.0f;

    playerColor.r = playerColor.r >> 2;
    playerColor.g = playerColor.g >> 2;
    playerColor.b = playerColor.b >> 2;
    playerColor.a = 255;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (checkDrawLine(x, y, (y & 1) - 1, -1, grid, -1, &isChosen, playerID, &isPlayer)) {
                DrawLineEx(
                    (Vector2) { grid[x][y].screen_coordinates.x - horiz, grid[x][y].screen_coordinates.y - vert },
                    (Vector2) { grid[x][y].screen_coordinates.x, grid[x][y].screen_coordinates.y - radius },
                    THICKNESS,
                    isPlayer ? playerColor : BLACK
                );
            }
            if (checkDrawLine(x, y, (y & 1) - 1, 1, grid, -1, &isChosen, playerID, &isPlayer)) {
                DrawLineEx(
                    (Vector2) { grid[x][y].screen_coordinates.x - horiz, grid[x][y].screen_coordinates.y + vert },
                    (Vector2) { grid[x][y].screen_coordinates.x, grid[x][y].screen_coordinates.y + radius },
                    THICKNESS,
                    isPlayer ? playerColor : BLACK
                );
            }
            if (checkDrawLine(x, y, y & 1, 1, grid, -1, &isChosen, playerID, &isPlayer)) {
                DrawLineEx(
                    (Vector2) { grid[x][y].screen_coordinates.x + horiz, grid[x][y].screen_coordinates.y + vert },
                    (Vector2) { grid[x][y].screen_coordinates.x, grid[x][y].screen_coordinates.y + radius },
                    THICKNESS,
                    isPlayer ? playerColor : BLACK
                );
            }
            if (checkDrawLine(x, y, y & 1, -1, grid, -1, &isChosen, playerID, &isPlayer)) {
                DrawLineEx(
                    (Vector2) { grid[x][y].screen_coordinates.x + horiz, grid[x][y].screen_coordinates.y - vert },
                    (Vector2) { grid[x][y].screen_coordinates.x, grid[x][y].screen_coordinates.y - radius },
                    THICKNESS,
                    isPlayer ? playerColor : BLACK
                );
            }
            if (checkDrawLine(x, y, -1, 0, grid, -1, &isChosen, playerID, &isPlayer)) {
                DrawLineEx(
                    (Vector2) { grid[x][y].screen_coordinates.x - horiz, grid[x][y].screen_coordinates.y + vert },
                    (Vector2) { grid[x][y].screen_coordinates.x - horiz, grid[x][y].screen_coordinates.y - vert },
                    THICKNESS,
                    isPlayer ? playerColor : BLACK
                );
            }
            if (checkDrawLine(x, y, 1, 0, grid, -1, &isChosen, playerID, &isPlayer)) {
                DrawLineEx(
                    (Vector2) { grid[x][y].screen_coordinates.x + horiz, grid[x][y].screen_coordinates.y + vert },
                    (Vector2) { grid[x][y].screen_coordinates.x + horiz, grid[x][y].screen_coordinates.y - vert },
                    THICKNESS,
                    isPlayer ? playerColor : BLACK
                );
            }
        }
    }

#undef THICKNESS
};

void DrawChosenPoliticalGridOutline(int radius, int width, int height, struct GridTile** grid, int chosenID) {
    int isChosen = 0;
    int isPlayer = 0;
    #define THICKNESS 20

    float horiz = sqrtf(3) * radius / 2.0f;
    float vert = radius / 2.0f;

    static double oscilations = 0;
    unsigned char currentPosition = (unsigned char)(127.5 * (sin(oscilations) + 1));
    Color currentColor = { .r = 255, .g = 255, .b = 255, .a = currentPosition };

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (checkDrawLine(x, y, (y & 1) - 1, -1, grid, chosenID, &isChosen, -1, &isPlayer)) {
                if (isChosen)
                DrawLineEx(
                    (Vector2) { grid[x][y].screen_coordinates.x - horiz, grid[x][y].screen_coordinates.y - vert }, 
                    (Vector2) { grid[x][y].screen_coordinates.x, grid[x][y].screen_coordinates.y - radius }, 
                    THICKNESS,
                    currentColor
                );
            }
            if (checkDrawLine(x, y, (y & 1) - 1, 1, grid, chosenID, &isChosen, -1, &isPlayer)) {
                if (isChosen)
                DrawLineEx(
                    (Vector2) { grid[x][y].screen_coordinates.x - horiz, grid[x][y].screen_coordinates.y + vert }, 
                    (Vector2) { grid[x][y].screen_coordinates.x, grid[x][y].screen_coordinates.y + radius },
                    THICKNESS,
                    currentColor
                );
            }
            if (checkDrawLine(x, y, y & 1, 1, grid, chosenID, &isChosen, -1, &isPlayer)) {
                if (isChosen)
                DrawLineEx(
                    (Vector2) { grid[x][y].screen_coordinates.x + horiz, grid[x][y].screen_coordinates.y + vert }, 
                    (Vector2) { grid[x][y].screen_coordinates.x, grid[x][y].screen_coordinates.y + radius }, 
                    THICKNESS,
                    currentColor
                );
            }
            if (checkDrawLine(x, y, y & 1, -1, grid, chosenID, &isChosen, -1, &isPlayer)) {
                if (isChosen)
                DrawLineEx(
                    (Vector2) { grid[x][y].screen_coordinates.x + horiz, grid[x][y].screen_coordinates.y - vert }, 
                    (Vector2) { grid[x][y].screen_coordinates.x, grid[x][y].screen_coordinates.y - radius }, 
                    THICKNESS,
                    currentColor
                );
            }
            if (checkDrawLine(x, y, -1, 0, grid, chosenID, &isChosen, -1, &isPlayer)) {
                if (isChosen)
                DrawLineEx(
                    (Vector2) { grid[x][y].screen_coordinates.x - horiz, grid[x][y].screen_coordinates.y + vert }, 
                    (Vector2) { grid[x][y].screen_coordinates.x - horiz, grid[x][y].screen_coordinates.y - vert }, 
                    THICKNESS,
                    currentColor
                );
            }
            if (checkDrawLine(x, y, 1, 0, grid, chosenID, &isChosen, -1, &isPlayer)) {
                if (isChosen)
                DrawLineEx(
                    (Vector2) { grid[x][y].screen_coordinates.x + horiz, grid[x][y].screen_coordinates.y + vert }, 
                    (Vector2) { grid[x][y].screen_coordinates.x + horiz, grid[x][y].screen_coordinates.y - vert }, 
                    THICKNESS,
                    currentColor
                );
            }
        }
    }

    oscilations += 0.02;
    #undef THICKNESS
};


void DrawCheckedPoliticalGridOutline(int radius, int width, int height, struct GridTile** grid, int chosenID, int playerID) {
    int isChosen = 0;
    int isPlayer = 0;
#define THICKNESS 20

    float horiz = sqrtf(3) * radius / 2.0f;
    float vert = radius / 2.0f;

    static double oscilations = 0;
    unsigned char currentPosition = (unsigned char)(127.5 * (sin(oscilations) + 1));
    Color currentColor = { .r = currentPosition, .g = currentPosition, .b = currentPosition, .a = 255 };

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (checkDrawLine(x, y, (y & 1) - 1, -1, grid, chosenID, &isChosen, playerID, &isPlayer)) {
                DrawLineEx(
                    (Vector2) {
                    grid[x][y].screen_coordinates.x - horiz, grid[x][y].screen_coordinates.y - vert
                },
                    (Vector2) {
                    grid[x][y].screen_coordinates.x, grid[x][y].screen_coordinates.y - radius
                },
                    THICKNESS,
                    isChosen ? currentColor : isPlayer ? WHITE : BLACK
                );
            }
            if (checkDrawLine(x, y, (y & 1) - 1, 1, grid, chosenID, &isChosen, playerID, &isPlayer)) {
                DrawLineEx(
                    (Vector2) {
                    grid[x][y].screen_coordinates.x - horiz, grid[x][y].screen_coordinates.y + vert
                },
                    (Vector2) {
                    grid[x][y].screen_coordinates.x, grid[x][y].screen_coordinates.y + radius
                },
                    THICKNESS,
                    isChosen ? currentColor : isPlayer ? WHITE : BLACK
                );
            }
            if (checkDrawLine(x, y, y & 1, 1, grid, chosenID, &isChosen, playerID, &isPlayer)) {
                DrawLineEx(
                    (Vector2) {
                    grid[x][y].screen_coordinates.x + horiz, grid[x][y].screen_coordinates.y + vert
                },
                    (Vector2) {
                    grid[x][y].screen_coordinates.x, grid[x][y].screen_coordinates.y + radius
                },
                    THICKNESS,
                    isChosen ? currentColor : isPlayer ? WHITE : BLACK
                );
            }
            if (checkDrawLine(x, y, y & 1, -1, grid, chosenID, &isChosen, playerID, &isPlayer)) {
                DrawLineEx(
                    (Vector2) {
                    grid[x][y].screen_coordinates.x + horiz, grid[x][y].screen_coordinates.y - vert
                },
                    (Vector2) {
                    grid[x][y].screen_coordinates.x, grid[x][y].screen_coordinates.y - radius
                },
                    THICKNESS,
                    isChosen ? currentColor : isPlayer ? WHITE : BLACK
                );
            }
            if (checkDrawLine(x, y, -1, 0, grid, chosenID, &isChosen, playerID, &isPlayer)) {
                DrawLineEx(
                    (Vector2) {
                    grid[x][y].screen_coordinates.x - horiz, grid[x][y].screen_coordinates.y + vert
                },
                    (Vector2) {
                    grid[x][y].screen_coordinates.x - horiz, grid[x][y].screen_coordinates.y - vert
                },
                    THICKNESS,
                    isChosen ? currentColor : isPlayer ? WHITE : BLACK
                );
            }
            if (checkDrawLine(x, y, 1, 0, grid, chosenID, &isChosen, playerID, &isPlayer)) {
                DrawLineEx(
                    (Vector2) {
                    grid[x][y].screen_coordinates.x + horiz, grid[x][y].screen_coordinates.y + vert
                },
                    (Vector2) {
                    grid[x][y].screen_coordinates.x + horiz, grid[x][y].screen_coordinates.y - vert
                },
                    THICKNESS,
                    isChosen ? currentColor : isPlayer ? WHITE : BLACK
                );
            }
        }
    }

    oscilations += 0.02;
#undef THICKNESS
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