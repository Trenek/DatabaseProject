#include <math.h>

#include "raylib.h"

#include "state.h"
#include "GridTileDef.h"

#include "drawMenuElement.h"
#include "ProvinceTextures.h"
#include "GetCivilizations.h"
#include "GetPoliticalDivision.h"

void mapDebug(enum state* state) {
    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    const int width = 25;
    const int height = 25;
    int radius = 40;
    int frontSize = 40;
    Vector2 chosen = { 0, 0 };
    int size = 0;

    float one = GetScreenWidth() / ((sqrtf(3) * radius) * (width + 3));
    float two = GetScreenHeight() / ((3.0 * radius / 2.0) * (float)(height + 3));

    Camera2D camera1 = {
        .target = (Vector2){ 950, 800 },
        .offset = (Vector2){ GetScreenWidth() / 2, GetScreenHeight() / 2},
        .rotation = 0.0f,
        .zoom = two > one ? one : two
    };

    float horiz = sqrtf(3) * radius / 2.0;
    float vert = radius;

    RenderTexture screenCamera1 = LoadRenderTexture(GetScreenWidth(), GetScreenHeight() + 20);
    Rectangle splitScreenRect = { 0.0f, 0.0f, (float)screenCamera1.texture.width, (float)-screenCamera1.texture.height };

    Texture2D* texture = LoadTextures(&size);
    Texture2D city[2];

    Image image = LoadImage("assets/City.png");
    city[0] = LoadTextureFromImage(image);
    UnloadImage(image);
    image = LoadImage("assets/CapitalCity.png");
    city[1] = LoadTextureFromImage(image);
    UnloadImage(image);

    struct GridTile** grid = allocGridTile(width, height, texture);

    int count = 0;
    struct Civilization* civilizations = GetCivilizations(&count, 1);

    bool political = true;

    GetPoliticalDivision(grid, 1);

    while (!WindowShouldClose() && *state == MAP_DEBUG) {
        if (IsKeyDown(KEY_A)) camera1.offset.x += 1 / camera1.zoom;
        if (IsKeyDown(KEY_D)) camera1.offset.x -= 1 / camera1.zoom;
        if (IsKeyDown(KEY_S)) camera1.offset.y -= 1 / camera1.zoom;
        if (IsKeyDown(KEY_W)) camera1.offset.y += 1 / camera1.zoom;

        if (IsKeyDown(KEY_LEFT)) camera1.target.x -= 1 / camera1.zoom;
        if (IsKeyDown(KEY_RIGHT)) camera1.target.x += 1 / camera1.zoom;
        if (IsKeyDown(KEY_DOWN)) camera1.target.y += 1 / camera1.zoom;
        if (IsKeyDown(KEY_UP)) camera1.target.y -= 1 / camera1.zoom;

        if (IsKeyDown(KEY_Q)) camera1.zoom += 0.01;
        if (IsKeyDown(KEY_E)) camera1.zoom -= 0.01;
        camera1.zoom += (GetMouseWheelMove() * camera1.zoom / 16);
        if (camera1.zoom < 0.1) camera1.zoom = 0.1;
        if (camera1.zoom > 10) camera1.zoom = 10;

        BeginTextureMode(screenCamera1);
            ClearBackground(BROWN);

            BeginMode2D(camera1);
                GenerateHexGrid(radius, width, height, grid);
                DrawVisibleFields(radius, width, height, grid, texture[size - 1]);
                if (political) DrawPoliticalDivision(radius, width, height, grid, civilizations);
                DrawCity(radius, width, height, grid, city);
                DrawPoliticalGridOutline(radius, width, height, grid);
                DrawHexGridOutline(radius, width, height, grid);
                //DEBUG_DrawCoordinatesOnHexGrid(radius, width, height, grid);
                drawMenuElement("Choose Your Country Fellow Citizen", frontSize, sqrtf(3) * radius * width / 2, 0, 10, 10, NULL, NULL);
                //DrawTexture(texture, GetScreenWidth() / 2 - texture.width / 2, GetScreenHeight() / 2 - texture.height / 2, WHITE);
                //DrawTextureEx(texture, (Vector2) { .x = 100 - horiz, .y = 100 - vert }, 0, (radius << 1) / 2579.0, WHITE);
            EndMode2D();
        EndTextureMode();

        BeginDrawing();
        ClearBackground(BROWN);
        DrawTextureRec(screenCamera1.texture, splitScreenRect, (Vector2) { 0, 0 }, WHITE);
        //DrawText(TextFormat("%f %f %f %f %f", camera1.offset.x, camera1.offset.y, camera1.target.x, camera1.target.y, camera1.zoom), 0, 0, 20, (Color) { .r = 0, .g = 0, .b = 0, .a = 255 });

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            checkClick(height, width, radius, grid, &chosen, camera1);
        }

        if (IsKeyPressed(KEY_P)) {
            Pause(state, MAP_DEBUG, &screenCamera1, &splitScreenRect);
        }

        if (IsKeyPressed(KEY_M)) {
            political = !political;
        }
    }

    UnloadRenderTexture(screenCamera1); // Unload render texture
    UnloadTextures(texture, size);
    UnloadTexture(city[0]);
    UnloadTexture(city[1]);
}