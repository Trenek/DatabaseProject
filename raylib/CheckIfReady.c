#include <stdio.h>
#include <string.h>

#include "query.h"

static int isReadyCheck(SQLHANDLE SQLStatementHandle, void* message) {
	int isReady = 1;

	if (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
		isReady = 0;
	}

	return isReady;
}

int checkIfReady(int sessionID) {
	char buffor[512] = { 0 };

	sprintf(buffor, "EXEC [CheckIfEveryoneIsReady] %i", sessionID);

	return QUERY(buffor, NULL, isReadyCheck, NULL);
}