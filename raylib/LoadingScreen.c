#include <stdio.h>

#include <raylib.h>

void LoadingScreen(int current, int max) {
    char buffor[8] = { 0 };

    sprintf(buffor, "%i%%", (100 * current) / max);

    BeginDrawing();

    ClearBackground((Color) { 0 });

    DrawText(buffor, (GetScreenWidth() - MeasureText(buffor, 100)) / 2, (GetScreenHeight() - 100) / 2, 100, (Color) { .r = 255, .g = 0, .b = 126, .a = 255 });

    EndDrawing();
}
