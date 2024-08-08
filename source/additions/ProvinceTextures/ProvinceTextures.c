#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <raylib.h>

#include "Terrain.h"

static void LoadingScreen(int current, int max) {
    char buffor[8] = { 0 };

    sprintf(buffor, "%i%%", (100 * current) / max);

    BeginDrawing();

    ClearBackground((Color) { 0 });

    DrawText(buffor, (GetScreenWidth() - MeasureText(buffor, 100)) / 2, (GetScreenHeight() - 100) / 2, 100, (Color) { .r = 255, .g = 0, .b = 126, .a = 255 });

    EndDrawing();
}

void addCityTexture(Texture2D* city, int size) {
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

Texture2D* LoadTextures(int* size) {
    Image image;
    int i = 0;
    char** terrain = GetTerrain(size);
    char buffor[255] = { 0 };
    Texture2D* texture = malloc(*size * sizeof(Texture2D));

    while (i < *size) {
        LoadingScreen(i, *size + 2);
        memset(buffor, 0, 255);
        sprintf(buffor, "assets/%s.png", terrain[i]);
        image = LoadImage(buffor);
        texture[i] = LoadTextureFromImage(image);
        UnloadImage(image);

        i += 1;
    }

    i = 0;
    while (i < *size) {
        free(terrain[i]);
        i += 1;
    }
    free(terrain);

    return texture;
}

void UnloadTextures(Texture2D* texture, int size) {
    int i = 0;

    while (i < size) {
        UnloadTexture(texture[i]);
        i += 1;
    }

    free(texture);
}