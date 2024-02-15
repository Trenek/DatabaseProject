#include <stdio.h>
#include <string.h>

#include "query.h"

int AddPlayer(char* errorMessageOut, int gameSession, int userID) {
	char buffor[256];
	char errorMessage[256] = "";

	sprintf(buffor, "EXECUTE dbo.[AddPlayer] %i, %i", gameSession, userID);

	QUERY(buffor, errorMessage, NULL, NULL);

	if (*errorMessage) {
		strcpy(errorMessageOut, strchr(errorMessage, ':') + 2);
	}

	return 0;
}