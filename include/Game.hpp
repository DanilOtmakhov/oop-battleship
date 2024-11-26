#ifndef GAME_HPP
#define GAME_HPP

#include "Player.hpp"
#include "Bot.hpp"
#include "AbilityManager.hpp"
#include "ConsoleDisplayer.hpp"
#include "InputHandler.hpp"

class Game {
    private:
        Player player;
        Bot bot;
        ConsoleDisplayer displayer = ConsoleDisplayer();
        InputHandler inputHandler = InputHandler();
    public:
        Game(Player player, Bot bot);
        void startGame();
        void gameRound();
        void gameOver();
        void saveGame();
        void loadGame();
};

#endif
