#ifndef INPUTBOX
#define INPUTBOX

#include <stdbool.h>

#include "raylib.h"

struct inputBox {
    char text[256];
    int length;
    int frontSize;
    int clicked;
    Rectangle coordinates;
};

void DrawInputBox(struct inputBox* input);
int updateInputBox(struct inputBox* input);

inline bool checkCoursor(struct inputBox* input) {
    return CheckCollisionPointRec(GetMousePosition(), input->coordinates);
};

#endif // !INPUTBOX