#ifndef PROVINCE_H
#define PROVINCE_H

#include "GridTileDef.h"

struct provinceInformation {
	char terrainName[255];
	char regionName[255];
	char cityName[255];
};

void GetProvinceInformation(int sessionID, int coordinateX, int coordinateY, struct provinceInformation* info);
void GetProvinces(struct GridTile** grid, Texture2D* texture, int mapID);
void GetSessionProvinces(struct GridTile** grid, Texture2D* texture, int sessionID);

#endif