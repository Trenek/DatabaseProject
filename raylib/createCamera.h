#include <math.h>
#include <raylib.h>

inline Camera2D createCamera(int width, int height, int radius) {
    float one = GetScreenWidth() / ((sqrtf(3) * radius) * (width + 3));
    float two = GetScreenHeight() / (((3 * radius * (height + 3)) / 2.0f) + (radius / 2.0f));

    height >>= 1;
    width >>= 1;

    return (Camera2D) {
        .target = (Vector2){ (sqrtf(3) * radius) * (width + 1) , ((3 * radius * (height + 1)) / 2.0f) + (radius / 2.0f) },
        .offset = (Vector2){ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f },
        .rotation = 0.0f,
        .zoom = two > one ? one : two
    };
}
