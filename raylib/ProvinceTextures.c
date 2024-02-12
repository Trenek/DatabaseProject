#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "raylib.h"

#include "GetTerrain.h"

Texture2D* LoadTextures(int* size) {
    Image image;
    int i = 0;
    char** terrain = GetTerrain(size);
    char buffor[255] = { 0 };
    Texture2D* texture = malloc(*size * sizeof(Texture2D));

    while (i < *size) {
        memset(buffor, 0, 255);
        sprintf(buffor, "assets/%s.png", terrain[i]);
        printf(buffor);
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