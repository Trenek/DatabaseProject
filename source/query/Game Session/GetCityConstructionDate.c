#include <stdio.h>
#include <string.h>

#include "query.h"

static int getCityConstructionDate(SQLHANDLE SQLStatementHandle, void* message) {
	char* date = (char*)message;

	if (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
		memset(date, 0, 255 * sizeof(char));

		SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, date, 255 * sizeof(char), NULL);
	}

	return 0;
}

void GetCityConstructionDate(char* date, int sessionID, int coordinateX, int coordinateY) {
	char buffor[512] = { 0 };

	sprintf(buffor, "EXECUTE dbo.[GetCityConstructionDate] %i, %i, %i", sessionID, coordinateX, coordinateY);
	QUERY(buffor, NULL, getCityConstructionDate, date);
}