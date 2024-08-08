#include <stdio.h>

#include "query.h"

int UpdateCurrentDate(int sessionID) {
	char buffor[512];

	sprintf(buffor, "EXECUTE dbo.[UpdateCurrentDate] %i", sessionID);

	return QUERY(buffor, NULL, NULL, NULL);
}

int UpdateCurrentDateBy10Days(int sessionID) {
	char buffor[512] = { 0 };
	int i = 10;

	while (i > 0) {
		sprintf(buffor, "%s;EXECUTE dbo.[UpdateCurrentDate] %i", buffor, sessionID);

		i -= 1;
	}

	return QUERY(buffor, NULL, NULL, NULL);
}