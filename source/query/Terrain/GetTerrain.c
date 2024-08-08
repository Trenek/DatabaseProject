#include <stdio.h>

#include "query.h"

static int getTerrainCount(SQLHANDLE SQLStatementHandle, [[maybe_unused]] void* message) {
	int size = 0;

	if (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
		SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &size, sizeof(size), NULL);
	}

	return size;
}


static int getTerrain(SQLHANDLE SQLStatementHandle, void* message) {
	char** buffor = (char**)message;
	int i = 0;

	while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
		SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &i, sizeof(i), NULL);
		buffor[i - 1] = malloc(255 * sizeof(char));
		SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, buffor[i - 1], sizeof(char) * 255, NULL);
	}

	return 0;
}

char** GetTerrain(int* size) {
	char** buffor;
	
	*size = QUERY("EXECUTE dbo.[GetTerrainCount]", NULL, getTerrainCount, NULL);

	buffor = malloc(*size * sizeof(char*));

	QUERY("EXECUTE dbo.[GetTerrain]", NULL, getTerrain, buffor);

	return buffor;
}
