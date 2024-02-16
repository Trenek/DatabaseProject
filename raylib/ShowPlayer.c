#include <stdio.h>

#include "query.h"

struct player {
	char* playerName;
	char* civilizationName;
	int* playerID;
	int* civilizationID;
};

static int showPlayer(SQLHANDLE SQLStatementHandle, void* message) {
	struct player player = *(struct player*)message;
	long long int nr = 0;
	char playerName[255] = { 0 };
	char civName[255] = { 0 };

	if (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
		SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &nr, sizeof(nr), NULL);
		SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, playerName, sizeof(playerName), NULL);
		SQLGetData(SQLStatementHandle, 3, SQL_C_DEFAULT, civName, sizeof(civName), NULL);
		SQLGetData(SQLStatementHandle, 4, SQL_C_DEFAULT, player.playerID, sizeof(*player.playerID), NULL);
		if (player.civilizationID != NULL) SQLGetData(SQLStatementHandle, 5, SQL_C_DEFAULT, player.civilizationID, sizeof(*player.civilizationID), NULL);

		if (*civName != 0) strcpy(player.civilizationName, civName);
		strcpy(player.playerName, playerName);
	}

	return (int)nr;
}

int ShowPlayer(char* playerName, char* civilizationName, int* playerID, int* civilizationID, int gameSession, int position) {
	char buffor[256];

	sprintf(buffor, "EXECUTE dbo.[ShowPlayer] %i, %i", gameSession, position);

	return QUERY(buffor, NULL, showPlayer, &(struct player) { playerName, civilizationName, playerID, civilizationID });
}