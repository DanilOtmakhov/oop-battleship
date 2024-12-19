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
        ConsoleDisplayer displayer;
    public:
        Game(Player player, Bot bot, GameState gameState, ConsoleDisplayer displayer);
        void botTurn();
        void handlePlayerAttack();
        void handlePlayerAbility();
        void handleExceptions();
        void resetBot();
        void resetGame();
        void saveGame();
        void loadGame();
        GameState& getGameState();
        bool isGameOver();
        bool isPlayerDefeated();
};

#endif
