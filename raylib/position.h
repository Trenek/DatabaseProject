#ifndef POSITION
#define POSITION

struct position {
    int x;
    int y;
    char incX;
    char incY;
};

inline void moveCube(struct position* cubePosition) {
    cubePosition->x += cubePosition->incX;
    cubePosition->y += cubePosition->incY;

    if (cubePosition->x == (GetScreenWidth() - 20) || cubePosition->x == 0) {
        cubePosition->incX = -cubePosition->incX;
    }
    if (cubePosition->y == (GetScreenHeight() - 20) || cubePosition->y == 0) {
        cubePosition->incY = -cubePosition->incY;
    }
}

#endif