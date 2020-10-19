#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "PlayerFactory.h"

class Game{
    public:
        ~Game();
        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;

        static Game& Get();
        static void StartGame();
        static void RestartGame();

    private:
        Game();
        Player* P1;
        Player* P2;
        int gameMode;

        void printOneRowTable(std::string firstOption, std::string secondOption);
        void choosePlayers();
        void Play();
        void Round();
};


#endif // GAME_H
