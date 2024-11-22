#ifndef GAME_HPP
#define GAME_HPP

#include "Player.hpp"
#include "AbilityManager.hpp"
#include "ConsoleDisplayer.hpp"
#include "InputHandler.hpp"


class Game {
    private:
        //Player& player;
        //Player& enemyPlayer;
        // ConsoleDisplayer displayer;
        // InputHandler InputHandler;
    public:
        void startGame();
        void gameRound();
        void gameOver();
        void saveGame();
        void loadGame();
};

#endif
