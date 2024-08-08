#include "inputBox.h"
#include "gameInformations.h"
#include "GetProvinceInformation.h"
#include "GridTileDef.h"
#include "state.h"
#include "GameSession.h"

union layers {
    struct layersS {
        unsigned char provinceInfo : 1;
        unsigned char countryInfo : 1;
        unsigned char buildingInfo : 1;
        unsigned char cityNameBox : 1;
        unsigned char errorLayer : 1;
    } indivLayers;
    unsigned char layers;
};

bool clickCityNameBox(union layers* topLayer, char* errorMessage, Rectangle cityNameRec, Vector2 chosen, struct inputBox *cityName, int* gold, bool* updatePlayer, struct gameInformations info);
bool clickProvinceLayer(union layers* topLayer, Vector2 chosen, struct provinceInformation provinceInfo, Rectangle provinceRec, char constructionDate[], struct GridTile** grid, struct building building[], int civilizationID);
bool clickCountryLayer(union layers* topLayer, Rectangle countryRec);
bool clickBuildingLayer(union layers* topLayer, Rectangle buildingRec);
bool clickDateForward(int position, Rectangle topRec, bool* updatePlayer, struct gameInformations info, char date[]);

bool drawCityNameBox(union layers topLayer, Rectangle cityNameRec, struct inputBox* cityName);
bool drawProvinceInfo(union layers topLayer, Rectangle provinceRec, struct provinceInformation provinceInfo, char* constructionDate, struct GridTile** grid, Vector2 chosen, int civilizationID);
bool drawCountryInfo(union layers topLayer, Rectangle countryRec);
bool drawBuildingInfo(union layers topLayer, Rectangle buildingRec, struct building building[]);
void drawTopLayer(Rectangle topRec, char* playerName, int gold, int position, char* date);

bool drawErrorLayer(union layers topLayer, char* errorMessage);

void mapChange(union layers* topLayer, int* position, bool* updatePlayer, Camera2D* camera1, enum state* state, RenderTexture screenCamera1, Rectangle splitScreenRect, bool* political, char playerName[], char civilizationName[], int* playerID, int* civilizationID, int* gold, struct gameInformations info);
void mapClick(union layers* topLayer, int height, int width, int radius, struct GridTile** grid, Vector2* chosen, Camera2D camera1, char* constructionDate, struct provinceInformation* provinceInfo, struct gameInformations info);