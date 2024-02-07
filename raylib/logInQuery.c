#define _CRT_SECURE_NO_WARNINGS

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

int logInQuery(char* bufforOUT, const char* login, const char* password) {
	char buffor[512];
	int ID = 0;

	sprintf(buffor, "EXEC [Login] @login = '%s', @password = '%s'", login, password);
	ID = QUERY(buffor, logInCheck, NULL);

	if (ID == 0) {
		strcpy(bufforOUT, strchr(buffor, ':') + 2);
	}

	return ID;
}