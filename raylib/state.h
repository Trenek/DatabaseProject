#ifndef STATE_DEFINE
#define STATE_DEFINE

#include "isMouseInRange.h"
#include "position.h"

enum state {
    MENU,
    LOAD_GAME,
    REGISTER,
    CUBE,
    PLAYER_LIST,
    CREATE_NEW_GAME,
    LOGIN,
    GAME_SETUP,
    PAUSE,
    EXIT
};

inline void clickAndChangeState(enum state* state, const char* text, int frontSize, int x, int y, int incX, int incY, enum state finalState) {
    if (isMouseInRange(x, y, incX, incY, frontSize, text))
        *state = finalState;
}

void menu(enum state* state);
void loadGame(enum state* state);
void cube(enum state* state);
void pause(enum state* state, Color* color, struct position cubePosition);
void Register(enum state* state);
void playerList(enum state* state);
void createGame(enum state* state);
void login(enum state* state);
void gameSetup(enum state* state);

#endif