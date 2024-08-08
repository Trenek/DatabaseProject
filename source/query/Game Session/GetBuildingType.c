#include <stdio.h>
#include <string.h>

#include "query.h"
#include "GameSession.h"

static int getBuildingType(SQLHANDLE SQLStatementHandle, void* message) {
	struct building* building = (struct building*)message;
		
	if (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
		SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &building->level, sizeof(building->level), NULL);
		SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &building->maxLevel, sizeof(building->maxLevel), NULL);
		SQLGetData(SQLStatementHandle, 3, SQL_C_DEFAULT, &building->tax, sizeof(building->tax), NULL);
		SQLGetData(SQLStatementHandle, 4, SQL_C_DEFAULT, &building->levies, sizeof(building->levies), NULL);
		SQLGetData(SQLStatementHandle, 5, SQL_C_DEFAULT, &building->price, sizeof(building->price), NULL);
		SQLGetData(SQLStatementHandle, 6, SQL_C_DEFAULT, building->name, sizeof(building->name), NULL);
	}

	return 0;
}

int GetBuildingType(int cityID, int typeID, int page, struct building* building) {
	char buffor[512] = { 0 };

	sprintf(buffor, "EXEC dbo.[GetBuildingType] %i, %i, %i", cityID, typeID, page);

	return QUERY(buffor, NULL, getBuildingType, (void*)building);
}