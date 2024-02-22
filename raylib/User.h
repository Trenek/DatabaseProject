struct player {
    int id;
    char name[128];
};

int logInQuery(char* errorMessage, const char* login, const char* password);
int GetUsers(struct player* players, int i);
void AddUser(char* errorMessage, const char* login, const char* password, const char* email);