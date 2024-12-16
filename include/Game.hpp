#ifndef GAME_HPP
#define GAME_HPP

#include "Player.hpp"
#include "Bot.hpp"
#include "AbilityManager.hpp"
#include "ConsoleDisplayer.hpp"
#include "InputHandler.hpp"
#include "GameState.hpp"

class Game {
    private:
        Player player;
        Bot bot;
        GameState gameState;
        bool gameEnded = false;
        ConsoleDisplayer displayer = ConsoleDisplayer();
        InputHandler inputHandler = InputHandler();
    public:
        Game(Player player, Bot bot, GameState gameState);
        void startGame();
        void initializeGame();
        void playerTurn();
        void botTurn();
        void handlePlayerAttack();
        void handlePlayerAbility();
        void checkGameOver();
        void handleExceptions();
        void resetBot();
        void resetGame();
};

#endif
