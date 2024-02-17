#include <stdio.h>
#include <string.h>

#include "GetProvinceInformation.h"
#include "query.h"

static int getProvinceInformation(SQLHANDLE SQLStatementHandle, void* message) {
	struct provinceInformation* info = (struct provinceInformation*)message;

	if (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
		memset(info->terrainName, 0, sizeof(info->terrainName));
		memset(info->regionName, 0, sizeof(info->regionName));
		memset(info->cityName, 0, sizeof(info->cityName));

		SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, info->terrainName, sizeof(info->terrainName), NULL);
		SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, info->regionName, sizeof(info->regionName), NULL);
		SQLGetData(SQLStatementHandle, 3, SQL_C_DEFAULT, info->cityName, sizeof(info->cityName), NULL);
	}

	return 0;
}

void GetProvinceInformation(int sessionID, int coordinateX, int coordinateY, struct provinceInformation* info) {
	char buffor[512] = { 0 };

	sprintf(buffor, "EXEC dbo.[GetProvinceInformation] %i, %i, %i", sessionID, coordinateX, coordinateY);
	QUERY(buffor, NULL, getProvinceInformation, info);
}