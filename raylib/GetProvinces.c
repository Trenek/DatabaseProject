#include <stdio.h>

#include "query.h"
#include "getGameSessions.h"
#include "GridTileDef.h"

struct twoVariables {
	struct GridTile** grid;
	Texture2D* texture;
};

static int getProvinces(SQLHANDLE SQLStatementHandle, void* message) {
	struct twoVariables two = *(struct twoVariables*) message;
	int x = 0;
	int y = 0;
	int terrainID = 0;

	while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
		SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &x, sizeof(x), NULL);
		SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &y, sizeof(y), NULL);
		SQLGetData(SQLStatementHandle, 3, SQL_C_DEFAULT, &terrainID, sizeof(terrainID), NULL);
		SQLGetData(SQLStatementHandle, 4, SQL_C_DEFAULT, &two.grid[x][y].CityID, sizeof(two.grid[x][y].CityID), NULL);

		two.grid[x][y].texture = &(two.texture)[terrainID - 1];
		two.grid[x][y].isClicked = false;
	}

	return 0;
}

void GetProvinces(struct GridTile** grid, Texture2D* texture, int mapID) {
	char bufforQuery[512];

	sprintf(bufforQuery, "EXECUTE dbo.[GetProvinces] %i", mapID);

	QUERY(bufforQuery, NULL, getProvinces, &(struct twoVariables) {.grid = grid, .texture = texture});
}