#include "inputBox.h"

#define MAX_INPUT_CHARS 128

#define BETWEEN(x, min, max) ((x) >= (min) && (x) <= (max))

void DrawInputBox(struct inputBox* input) {
    static int framesCounter = 0;
    int first = 0;

    DrawRectangleRec(input->coordinates, LIGHTGRAY);
    DrawRectangleLines((int)input->coordinates.x, (int)input->coordinates.y, (int)input->coordinates.width, (int)input->coordinates.height, input->clicked ? RED : DARKGRAY);

    while (MeasureText(input->text + first, input->frontSize) + 24 > input->coordinates.width) {
        first += 1;
    }
    DrawText(input->text + first, (int)input->coordinates.x + 5, (int)input->coordinates.y + 8, input->frontSize, MAROON);

    if (input->clicked) {
        if (((framesCounter / 100) % 2) == 0) {
            DrawText("_", (int)input->coordinates.x + 8 + MeasureText(input->text + first, input->frontSize), (int)input->coordinates.y + 12, input->frontSize, MAROON);
        }

        framesCounter += 1;
    }

}

#define BACKSPACE 100

int updateInputBox(struct inputBox* input) {
    int key = 0;
    static int backspace = 0;
    static int interval = 0;

    if (input->clicked) {
        while ((key = GetCharPressed()) > 0) {
            if (BETWEEN(key, 32, 125) && (input->length < MAX_INPUT_CHARS)) {
                input->text[input->length] = (char)key;
                input->text[input->length + 1] = '\0';
                input->length++;
            }
        }

        if ((backspace < BACKSPACE ? IsKeyPressed : IsKeyDown)(KEY_BACKSPACE)) {
            if (interval == 0) {
                if (input->length > 0) {
                    input->length -= 1;
                }
            }

            input->text[input->length] = '\0';
        }

        if (IsKeyDown(KEY_BACKSPACE)) {
            backspace += 1;
            interval += 1;
        }
        else {
            backspace = 0;
            interval = 0;
        }

        if (interval > 5) {
            interval = 0;
        }
    }

    return 0;
}