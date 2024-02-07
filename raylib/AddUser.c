#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#include "query.h"

void AddUser(char* bufforOUT, const char* login, const char* password, const char* email) {
	char buffor[512];

	sprintf(buffor, "EXEC AddNewUser @login = '%s', @password = '%s', @email = '%s'", login, password, email);
	QUERY(buffor, NULL, NULL);

	if (strncmp(buffor, "EXEC AddNewUser @login = ", 25) != 0) {
		strcpy(bufforOUT, strchr(buffor, ':') + 2);
	}
}