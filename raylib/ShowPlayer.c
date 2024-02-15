#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "query.h"

struct player {
	char* playerName;
	char* civilizationName;
	int* playerID;
};

/**/
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

		if (*civName != 0) strcpy(player.civilizationName, civName);
		strcpy(player.playerName, playerName);
		printf("%s\n", player.civilizationName);
	}

	return (int)nr;
}

int ShowPlayer(char* playerName, char* civilizationName, int* playerID, int gameSession, int position) {
	int nr = 0;
	char buffor[256];

	sprintf(buffor, "EXECUTE dbo.[ShowPlayer] %i, %i", gameSession, position);

	return QUERY(buffor, NULL, showPlayer, &(struct player) { playerName, civilizationName, playerID });
}