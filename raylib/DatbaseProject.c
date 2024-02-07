// raylib.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "raylib.h"

#include "state.h"

int loggedInID = 0;

int main(void) {
    enum state state = MENU;
    void (*function[])(enum state* state) = { 
        [MENU] = menu, 
        [PLAY] = play, 
        [REGISTER] = Register, 
        [CUBE] = cube, 
        [PLAYER_LIST] = playerList, 
        [CREATE_NEW_GAME] = createGame, 
        [LOAD_GAME] = play, 
        [LOGIN] = login
    };

    InitWindow(800, 600, "Project");

    SetTargetFPS(240);

    while (!WindowShouldClose() && (state != EXIT)) {
        function[state](&state);
    }

    rlCloseWindow();

    return 0;
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
