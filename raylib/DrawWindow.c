#include "raylib.h"

#include "getXY.h"

#define BETWEEN(xD, yD) ((xD) >= yD.x && (xD) <= yD.y)

void drawMenuElement(Color* color, const char* text, int frontSize, int x, int y, int plusX, int plusY) {
    x -= MeasureText(text, frontSize) >> 1;

    if (color != NULL) DrawRectangle(x - plusX, y - plusY, MeasureText(text, frontSize) + (plusX << 1), frontSize + (plusY << 1), *color);
    DrawText(text, x, y, frontSize, (Color) { .b = 42, .g = 58, .r = 45, .a = 255 });
}

void drawMenuElementResponsive(Color* color, const char* text, int frontSize, int x, int y, int plusX, int plusY, Color* newBackground) {
    if (BETWEEN(GetMousePosition().x, getX(x, plusX, frontSize, text)) && BETWEEN(GetMousePosition().y, getY(y, plusY, frontSize, text)))
        drawMenuElement(newBackground, text, frontSize, x, y, plusX, plusY);
    else
        drawMenuElement(color, text, frontSize, x, y, plusX, plusY);
}