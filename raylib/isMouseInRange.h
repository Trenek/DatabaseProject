#ifndef BAJOJAJO
#define BAJOJAJO

#include "raylib.h"

#define BETWEEN(x, min, max) ((x) >= (min) && (x) <= (max))

inline bool isMouseInRange(int x, int y, int incX, int incY, int frontSize, const char* text) {
    bool result = true;
    Vector2 mouse = GetMousePosition();
    x -= MeasureText(text, frontSize) >> 1;

    if (!BETWEEN(mouse.x, x - incX, x + MeasureText(text, frontSize) + incX)) {
        result = false;
    }
    else if (!BETWEEN(mouse.y, y - incY, y + frontSize + incY)) {
        result = false;
    }

    return result;
}

#endif // !BAJOJAJO