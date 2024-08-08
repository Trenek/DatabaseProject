#include <stdio.h>

#include "query.h"

static int getCurrentDate(SQLHANDLE SQLStatementHandle, void* message) {
	char* date = (char*)message;
	int isFirstDayOfTheMonth = 0;

	if (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
		SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, date, sizeof(char) * 255, NULL);
		SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &isFirstDayOfTheMonth, sizeof(isFirstDayOfTheMonth), NULL);
	}

	return isFirstDayOfTheMonth;
}

int GetCurrentDate(char* date, int sessionID) {
	char buffor[512] = { 0 };

	sprintf(buffor, "EXECUTE dbo.[GetCurrentDate] %i", sessionID);

	return QUERY(buffor, NULL, getCurrentDate, date);
}