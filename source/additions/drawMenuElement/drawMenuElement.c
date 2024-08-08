#include <raylib.h>
#include <stddef.h>

#include "isMouseInRange.h"

void drawMenuElement(const char* text, int frontSize, int x, int y, int incX, int incY, Color* color, Color* newColor) {
    if (isMouseInRange(x, y, incX, incY, frontSize, text)) {
        color = newColor;
    }

    x -= MeasureText(text, frontSize) >> 1;

    if (color != NULL) DrawRectangle(x - incX, y - incY, MeasureText(text, frontSize) + (incX << 1), frontSize + (incY << 1), *color);

    DrawText(text, x, y, frontSize, (Color) { .b = 42, .g = 58, .r = 45, .a = 255 });
}

void drawTextWithBoxBehind(const char* text, int frontSize, int x, int y, int incX, int incY, Color* color) {
    DrawRectangle(x - (incX >> 1), y - (incY >> 2), incX, incY, *color);

    x -= MeasureText(text, frontSize) >> 1;

    DrawText(text, x, y, frontSize, (Color) { .b = 42, .g = 58, .r = 45, .a = 255 });
}