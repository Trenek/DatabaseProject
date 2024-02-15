#include <stdio.h>

#include "query.h"
#include "GetCivilizations.h"

extern Color GetColor(unsigned int hexValue);                                // Get Color structure from hexadecimal value

static int getCivilizations(SQLHANDLE SQLStatementHandle, void* message) {
	long long index = 0;
	struct Civilization* two = (struct Civilization*)message;
	unsigned int rgba = 0;

	while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
		SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &index, sizeof(index), NULL);
		SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &two[index].CivilizationID, sizeof(two[index].CivilizationID), NULL);
		SQLGetData(SQLStatementHandle, 3, SQL_C_DEFAULT, &rgba, sizeof(rgba), NULL);
		SQLGetData(SQLStatementHandle, 4, SQL_C_DEFAULT, two[index].name, sizeof(two[index].name), NULL);
		two[index].color = GetColor((unsigned int)rgba);
	}

	return 0;
}

static int countCivilizations(SQLHANDLE SQLStatementHandle, void* message) {
	int count = 0;

	if (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
		SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &count, sizeof(count), NULL);
	}

	return count;
}

struct Civilization* GetCivilizations(int mapID) {
	struct Civilization* civilization;
	char bufforQuery[512];
	int count = 0;

	sprintf(bufforQuery, "EXECUTE dbo.[CountCivilizations] %i", mapID);

	count = QUERY(bufforQuery, NULL, countCivilizations, NULL);
	civilization = malloc(count * sizeof(struct Civilization));

	sprintf(bufforQuery, "EXECUTE dbo.[GetCivilizations] %i", mapID);

	QUERY(bufforQuery, NULL, getCivilizations, civilization);

	return civilization;
}
