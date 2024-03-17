#ifndef GAMESESSION_H
#define GAMESESSION_H

struct gameSession {
	int nr;
	int id;
	char name[128];
	char owner[128];
};

struct building {
	int level;
	int maxLevel;
	int tax;
	int levies;
	int price;
	int page;
	char name[255];
};

int checkIfReady(int sessionID);
int createGameSession(const char* saveName, int creatorID, int mapID, char* errorMessage);
int GetCurrentDate(char* date, int sessionID);
int GetGameSessions(struct gameSession* sessions, int page, int ownerID);
int UpdateCurrentDate(int sessionID);
int BuildCity(char* errorMessageOut, int sessionID, int coordinateX, int coordinateY, const char* name);
void GetCityConstructionDate(char* date, int sessionID, int coordinateX, int coordinateY);
int GetBuildingType(int cityID, int typeID, int page, struct building* building);
int UpdateCurrentDateBy10Days(int sessionID);

#endif