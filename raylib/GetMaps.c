#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "query.h"

#include "GetMaps.h"

static int getMaps(SQLHANDLE SQLStatementHandle, void* message) {
	struct map* map = (struct map*)message;
	int i = 0;
	int exists = 0;

	while (i < 10) {
		map[i].nr = 0;
		i += 1;
	}

	i = 0;
	while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
		SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &map[i].nr, sizeof(map[i].nr), NULL);
		SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, map[i].name, sizeof(map[i].name), NULL);
		SQLGetData(SQLStatementHandle, 3, SQL_C_DEFAULT, &map[i].id, sizeof(map[i].id), NULL);
		i += 1;
		exists = 1;
	}

	return exists;
}

int GetMaps(struct map* sessions, int page) {
	char buffor[512];

	sprintf(buffor, "EXECUTE dbo.[GetMaps] %i", page);

	return QUERY(buffor, NULL, getMaps, sessions);
}