#include <stdio.h>
#include <string.h>

#include "query.h"

int BuildCity(char* errorMessageOut, int sessionID, int coordinateX, int coordinateY, const char* name) {
	char buffor[512] = { 0 };
	char errorMessage[512] = { 0 };
	char* pos = NULL;

	*errorMessageOut = 0;
	sprintf(buffor, "EXECUTE dbo.[BuildCity] %i, %i, %i, '%s'", sessionID, coordinateX, coordinateY, name);
	QUERY(buffor, errorMessage, NULL, NULL);

	if (*errorMessage != 0) {
		pos = strchr(errorMessage, ':');
		strcpy(errorMessageOut, pos ? pos + 2 : errorMessage);
	}

	return 0;
}