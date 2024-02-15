#include <stdio.h>

#include "query.h"
#include "getGameSessions.h"

static int getGameSession(SQLHANDLE SQLStatementHandle, void* message) {
	struct gameSession* gameSession = (struct gameSession*)message;
	int i = 0;
	int exists = 0;

	while (i < 10) {
		gameSession[i].nr = 0;
		i += 1;
	}

	i = 0;
	while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
		SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &gameSession[i].nr, sizeof(gameSession[i].nr), NULL);
		SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, gameSession[i].name, sizeof(gameSession[i].name), NULL);
		SQLGetData(SQLStatementHandle, 3, SQL_C_DEFAULT, &gameSession[i].id, sizeof(gameSession[i].id), NULL);
		i += 1;
		exists = 1;
	}

	return exists;
}

int GetGameSessions(struct gameSession* sessions, int page, int ownerID) {
	char buffor[512];

	sprintf(buffor, "EXECUTE dbo.[ShowGameSessions] %i, %i", page, ownerID);

	return QUERY(buffor, NULL, getGameSession, sessions);
}