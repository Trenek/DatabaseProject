#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#include "query.h"

void AddUser(char* errorMessageOut, const char* login, const char* password, const char* email) {
	char buffor[512] = { 0 };
	char errorMessage[512] = { 0 };
	char* pos = NULL;

	*errorMessageOut = 0;
	sprintf(buffor, "EXEC AddNewUser @login = '%s', @password = '%s', @email = '%s'", login, password, email);
	QUERY(buffor, errorMessage, NULL, NULL);

	if (*errorMessage != 0) {
		pos = strchr(errorMessage, ':');
		strcpy(errorMessageOut, pos ? pos + 2 : errorMessage);
	}
}