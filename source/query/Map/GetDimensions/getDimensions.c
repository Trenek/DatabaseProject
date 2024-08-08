#include <stdio.h>

#include "query.h"
#include "GetCivilizations.h"

extern Color GetColor(unsigned int hexValue);                                // Get Color structure from hexadecimal value

static int countCivilizations(SQLHANDLE SQLStatementHandle, void* message) {
	int width = 0;
	int height = 0;

	if (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
		SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &width, sizeof(width), NULL);
		SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &height, sizeof(height), NULL);
	}

	*(int*)message = height;
	return width;
}

void GetSessionDimensions(int* width, int* height, int sessionID) {
	char bufforQuery[512];

	sprintf(bufforQuery, "EXECUTE dbo.[GetSessionDimensions] %i", sessionID);

	*width = QUERY(bufforQuery, NULL, countCivilizations, height);
}

void GetMapDimensions(int* width, int* height, int mapID) {
	char bufforQuery[512];

	sprintf(bufforQuery, "EXECUTE dbo.[GetMapDimensions] %i", mapID);

	*width = QUERY(bufforQuery, NULL, countCivilizations, height);
}