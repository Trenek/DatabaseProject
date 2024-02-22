int ShowPlayer(char* playerName, char* civilizationName, int* playerID, int* civilizationID, int* gold, int gameSession, int position);
void RemovePlayer(int playerID);
void AssignCivilization(char* errorMessageOut, int playerID, int civilization, int gameSession);
int AddPlayer(char* errorMessageOut, int gameSession, int userID);