#include <stdio.h>

#include "query.h"

int UpdateCurrentDate(int sessionID) {
	char buffor[512];

	sprintf(buffor, "EXECUTE dbo.[UpdateCurrentDate] %i", sessionID);

	return QUERY(buffor, NULL, NULL, NULL);
}