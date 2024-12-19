#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include "Game.hpp"

template <class Input, class Output>
class GameController {
private:
    Game& game;
    Input& input;
    Output& output;
    bool gameEnded = false;

public:
    GameController(Game& game, Input& input, Output& output)
        : game(game), input(input), output(output) {}

    void initializeGame() {
        output.displayGameStartInfo(input.getCommands());
        Command command = input.handleCommandInput();
        switch (command) {
            case Command::info:
                output.displayInfo(input.getCommands());
                initializeGame();
                break;
            case Command::start:
                startGame();
                break;
            case Command::save:
                output.displaySavingGame();
                game.saveGame();
                initializeGame();
                break;
            case Command::load:
                output.displayLoadingGame();
                game.loadGame();
                output.displayFields(game.getGameState().getPlayer().getField(), game.getGameState().getBot().getField());
                initializeGame();
                break;
            case Command::quit:
                gameEnded = true;
                break;
            default:
                output.displayIncorrectCommandInput();
                initializeGame();
                break;
        }
    }

    void startGame() {
        output.displayFields(game.getGameState().getPlayer().getField(), game.getGameState().getBot().getField());
        while (!gameEnded) {
            handlePlayerTurn();
            checkGameOver();
            if (gameEnded) break;
            handleBotTurn();
            checkGameOver();
        }
    }

    void handlePlayerTurn() {
        output.displayInfo(input.getCommands());
        Command command = input.handleCommandInput();
        try {
            switch (command) {
                case Command::info:
                    output.displayInfo(input.getCommands());
                case Command::attack:
                    game.handlePlayerAttack();
                    break;
                case Command::ability:
                    game.handlePlayerAbility();
                    break;
                case Command::save:
                    output.displaySavingGame();
                    game.saveGame();
                    handlePlayerTurn();
                    break;
                case Command::load:
                    output.displayLoadingGame();
                    game.loadGame();
                    output.displayFields(game.getGameState().getPlayer().getField(), game.getGameState().getBot().getField());
                    handlePlayerTurn();
                    break;
                case Command::quit:
                    gameEnded = true;
                    break;
                default:
                    output.displayIncorrectCommandInput();
                    handlePlayerTurn();
                    break;
            }
        }
        catch (...) {
            game.handleExceptions();
            handlePlayerTurn();
        }
    }

    void handleBotTurn() {
        game.botTurn();
        //output.displayFields(game.getGameState().getPlayer().getField(), game.getGameState().getBot().getField());
    }

    void checkGameOver() {
        if (game.isGameOver()) {
            gameEnded = true;
            if (game.isPlayerDefeated()) {
                output.displayFields(game.getGameState().getPlayer().getField(), game.getGameState().getBot().getField());
                output.displayBotWins();

                output.displayNewGame();
                char choice = input.handleYesOrNo();
                switch (choice) {
                    case 'N':
                    case 'n':
                        gameEnded = true;
                        break;
                    case 'Y':
                    case 'y':
                        gameEnded = false;
                        game.resetGame();
                        startGame();
                        break;
                    default:
                        output.displayIncorrectCommandInput();
                        break;
                }
            } else {
                output.displayFields(game.getGameState().getPlayer().getField(), game.getGameState().getBot().getField());
                output.displayPlayerWins();

                output.displayContinueGame();
                char choice = input.handleYesOrNo();
                switch (choice) {
                    case 'N':
                    case 'n':
                        gameEnded = true;
                        break;
                    case 'Y':
                    case 'y':
                        gameEnded = false;
                        game.resetBot();
                        startGame();
                        break;
                    default:
                        output.displayIncorrectCommandInput();
                        break;
                }
            }
        }
    }
};

#endif
