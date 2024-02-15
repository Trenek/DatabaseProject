#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "query.h"

void AssignCivilization(char* errorMessageOut, int playerID, int civilization, int gameSession) {
	char buffor[512] = { 0 };
	char errorMessage[512] = { 0 };

	sprintf(buffor, "EXECUTE dbo.[AssignCivilization] %i, %i, %i", playerID, civilization, gameSession);
	QUERY(buffor, errorMessage, NULL, NULL);

	if (*errorMessage != 0) {
		strcpy(errorMessageOut, strchr(errorMessage, ':') + 2);
	}
}