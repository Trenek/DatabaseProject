#include <stdio.h>
#include <string.h>

#include "query.h"

static int logInCheck(SQLHANDLE SQLStatementHandle, void* message) {
	int ID = 0;

	if (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
		SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &ID, sizeof(ID), NULL);
	}

	return ID;
}

int logInQuery(char* errorMessageOut, const char* login, const char* password) {
	char buffor[512] = { 0 };
	char errorMessage[512] = { 0 };
	int ID = 0;
	char* pos = 0;

	*errorMessageOut = 0;
	sprintf(buffor, "EXEC [Login] @login = '%s', @password = '%s'", login, password);
	ID = QUERY(buffor, errorMessage, logInCheck, NULL);

	if (*errorMessage != 0) {
		pos = strchr(errorMessage, ':');
		strcpy(errorMessageOut, pos ? pos + 2 : errorMessage);
	}

	return ID;
}