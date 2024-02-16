#include <stdio.h>

#include "query.h"

void RemovePlayer(int playerID) {
	char buffor[512] = { 0 };

	sprintf(buffor, "EXEC [RemovePlayer] %i", playerID);

	QUERY(buffor, NULL, NULL, NULL);
}