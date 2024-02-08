#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "query.h"
#include "GetUsers.h"

static int getUsers(SQLHANDLE SQLStatementHandle, void* message) {
	struct player* players = (struct player*)message;
	int i = 0;
	int exists = 0;

	while (i < 10) {
		players[i].id = 0;
		i += 1;
	}

	i = 0;
	while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
		SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &players[i].id, sizeof(players[i].id), NULL);
		SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, players[i].name, sizeof(players[i].name), NULL);
		i += 1;
		exists = 1;
	}

	return exists;
}

int GetUsers(struct player* players, int i) {
	char buffor[512] = { 0 };

	sprintf(buffor, "EXEC [ShowUsers] %i", i);

	return QUERY(buffor, NULL, getUsers, (void*)players);
}