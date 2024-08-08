#include <stdio.h>
#include <string.h>

#include "query.h"

static int getGameSession(SQLHANDLE SQLStatementHandle, [[maybe_unused]] void* message) {
	int id = 0;

	if (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
		SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &id, sizeof(id), NULL);
	}

	return id;
}

int createGameSession(const char* saveName, int creatorID, int mapID, char* errorMessageOut) {
	char buffor[512] = { 0 };
	char errorMessage[512] = { 0 };
	char* pos = NULL;
	int id = 0;

	*errorMessageOut = 0;
	sprintf(buffor, "EXECUTE dbo.[CreateGameSession] '%s', %i, %i", saveName, creatorID, mapID);
	QUERY(buffor, errorMessage, NULL, NULL);

	if (*errorMessage != 0) {
		pos = strchr(errorMessage, ':');
		strcpy(errorMessageOut, pos ? pos + 2 : errorMessage);
	}
	else {
		sprintf(buffor, "EXECUTE dbo.[GetGameSessionID] '%s', %i", saveName, creatorID);
		id = QUERY(buffor, errorMessage, getGameSession, NULL);
	}

	return id;
}
