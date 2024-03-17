#include <stdbool.h>
#include <raylib.h>

#include "play.h"
#include "gameInformations.h"
#include "Player.h"
#include "state.h"
#include "GridTileDef.h"
#include "GameSession.h"

void mapChange(union layers* topLayer, int* position, bool* updatePlayer, Camera2D camera1, enum state* state, RenderTexture screenCamera1, Rectangle splitScreenRect, bool* political, char playerName[], char civilizationName[], int* playerID, int* civilizationID, int* gold, struct gameInformations info) {
    if (!topLayer->indivLayers.cityNameBox) {
        if (IsKeyPressed(KEY_A)) if (*position > 1) {
            *position -= 1;
            *updatePlayer = true;
        }
        if (IsKeyPressed(KEY_D)) {
            if (ShowPlayer(playerName, civilizationName, playerID, civilizationID, gold, info.sessionID, *position + 1)) {
                *position += 1;
            }
            *updatePlayer = true;
        }

        if (IsKeyDown(KEY_LEFT)) camera1.target.x -= 1 / camera1.zoom;
        if (IsKeyDown(KEY_RIGHT)) camera1.target.x += 1 / camera1.zoom;
        if (IsKeyDown(KEY_DOWN)) camera1.target.y += 1 / camera1.zoom;
        if (IsKeyDown(KEY_UP)) camera1.target.y -= 1 / camera1.zoom;

        if (IsKeyDown(KEY_Q)) camera1.zoom += 0.01f;
        if (IsKeyDown(KEY_E)) camera1.zoom -= 0.01f;
        camera1.zoom += (GetMouseWheelMove() * camera1.zoom / 16);
        if (camera1.zoom < 0.1) camera1.zoom = 0.1f;
        if (camera1.zoom > 10) camera1.zoom = 10.0f;

        if (IsKeyPressed(KEY_P)) {
            Pause(state, PLAY, &screenCamera1, &splitScreenRect);
        }

        if (IsKeyPressed(KEY_M)) {
            *political = !*political;
        }
    }
}

void mapClick(union layers* topLayer, int height, int width, int radius, struct GridTile** grid, Vector2* chosen, Camera2D camera1, char* constructionDate, struct provinceInformation* provinceInfo, struct gameInformations info) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        checkClick(height, width, radius, grid, chosen, camera1);
        topLayer->layers = 0;
        if (chosen->x != -1) {
            *constructionDate = 0;
            GetProvinceInformation(info.sessionID, (int)chosen->x, (int)chosen->y, provinceInfo);
            GetCityConstructionDate(constructionDate, info.sessionID, (int)chosen->x, (int)chosen->y);
            topLayer->indivLayers.provinceInfo = 1;
        }
    }
    else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        checkClick(height, width, radius, grid, chosen, camera1);
        topLayer->layers = 0;
        if (chosen->x != -1)
            if (grid[(int)chosen->x][(int)chosen->y].civilizationID > 0) {
                topLayer->indivLayers.countryInfo = 1;
            }
    }
}