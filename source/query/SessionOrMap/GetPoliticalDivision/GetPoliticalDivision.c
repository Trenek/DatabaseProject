#include <stdio.h>

#include "query.h"
#include "GridTileDef.h"

static int getProvinces(SQLHANDLE SQLStatementHandle, void* message) {
	struct GridTile** grid = (struct GridTile**)message;
	int x = 0;
	int y = 0;

	while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
		SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &x, sizeof(x), NULL);
		SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &y, sizeof(y), NULL);
		SQLGetData(SQLStatementHandle, 3, SQL_C_DEFAULT, &grid[x][y].regionID, sizeof(grid[x][y].regionID), NULL);
		SQLGetData(SQLStatementHandle, 4, SQL_C_DEFAULT, &grid[x][y].civilizationID, sizeof(grid[x][y].civilizationID), NULL);
		SQLGetData(SQLStatementHandle, 5, SQL_C_DEFAULT, &grid[x][y].civilizationNumber, sizeof(grid[x][y].civilizationNumber), NULL);
		SQLGetData(SQLStatementHandle, 6, SQL_C_DEFAULT, &grid[x][y].isCapital, sizeof(grid[x][y].isCapital), NULL);
	}

	return 0;
}

void GetPoliticalDivision(struct GridTile** grid, int mapID) {
	char bufforQuery[512];

	sprintf(bufforQuery, "EXECUTE dbo.[GetPoliticalDivision] %i", mapID);

	QUERY(bufforQuery, NULL, getProvinces, grid);
}

void GetSessionPoliticalDivision(struct GridTile** grid, int sessionID) {
	char bufforQuery[512];

	sprintf(bufforQuery, "EXECUTE dbo.[GetSessionPoliticalDivision] %i", sessionID);

	QUERY(bufforQuery, NULL, getProvinces, grid);
}