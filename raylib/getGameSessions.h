struct gameSession {
	int nr;
	int id;
	char name[128];
	char owner[128];
};

int GetGameSessions(struct gameSession* sessions, int page, int ownerID);