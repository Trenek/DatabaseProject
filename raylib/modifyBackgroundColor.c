#include <raylib.h>

void modifyBackgroundColor(Color* color) {
    if (IsKeyDown(KEY_RIGHT)) {
        if (IsKeyDown(KEY_ONE))
            if (color->r < 255)
                color->r += 1;
        if (IsKeyDown(KEY_TWO))
            if (color->g < 255)
                color->g += 1;
        if (IsKeyDown(KEY_THREE))
            if (color->b < 255)
                color->b += 1;
        if (IsKeyDown(KEY_FOUR))
            if (color->a < 255)
                color->a += 1;
    }
    if (IsKeyDown(KEY_LEFT)) {
        if (IsKeyDown(KEY_ONE))
            if (color->r > 0)
                color->r -= 1;
        if (IsKeyDown(KEY_TWO))
            if (color->g > 0)
                color->g -= 1;
        if (IsKeyDown(KEY_THREE))
            if (color->b > 0)
                color->b -= 1;
        if (IsKeyDown(KEY_FOUR))
            if (color->a > 0)
                color->a -= 1;
    }
}
