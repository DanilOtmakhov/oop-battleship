#include "../include/Game.hpp"

Game::Game(Player player, Bot bot, GameState gameState) : player(player), bot(bot), gameState(gameState) {}

void Game::startGame() {
    displayer.displayFields(player.getField(), bot.getField());
    while (!gameEnded) {
        playerTurn();
        checkGameOver();
        if (gameEnded) break;
        botTurn();
        checkGameOver();
    }
}

void Game::initializeGame() {
    displayer.displayGameStart();
    int choise = inputHandler.handleChoise();
    switch (choise) {
        case 1:
            startGame();
            break;
        case 2:
            displayer.displaySavingGame();
            gameState.saveGame("/Users/danilotmakhov/Desktop/oop/battleship/saveFile.json");
            //initializeGame();
            startGame();
            break;
        case 3:
            displayer.displayLoadingGame();
            try {
                gameState.loadGame("/Users/danilotmakhov/Desktop/oop/battleship/saveFile.json");
            } catch (SaveFileHashMismatchException(exception)) {
                displayer.displayException(exception);
            } catch (nlohmann::json::parse_error(exception)) {
                displayer.displayException(exception);
            }
            displayer.displayFields(player.getField(), bot.getField());
            initializeGame();
            break;
        case 4:
            gameEnded = true;
            break;
        default:
            displayer.displayIncorrectChoiсeInput();
            break;
    }
}

void Game::playerTurn() {
    displayer.displayAttackOrApplyAbility();
    int playerChoice = inputHandler.handleChoise();
    try {
        switch (playerChoice) {
            case 1:
                handlePlayerAttack();
                break;
            case 2:
                handlePlayerAbility();
                break;
            case 3:
                displayer.displaySavingGame();
                gameState.saveGame("/Users/danilotmakhov/Desktop/oop/battleship/saveFile.json");
                playerTurn();
                break;
            case 4:
                displayer.displayLoadingGame();
                try {
                    gameState.loadGame("/Users/danilotmakhov/Desktop/oop/battleship/saveFile.json");
                } catch (SaveFileHashMismatchException(exception)) {
                    displayer.displayException(exception);
                }
                displayer.displayFields(player.getField(), bot.getField());
                playerTurn();
                break;
            case 5:
                gameEnded = true;
                break;
            default:
                displayer.displayIncorrectChoiсeInput();
                break;
        }
    } catch (...) {
        handleExceptions();
        playerTurn();
    }
}

void Game::botTurn() {
    try {
        bot.attack();
        displayer.displayFields(player.getField(), bot.getField());
    } catch (...) {
        handleExceptions();
        botTurn();
    }
}

void Game::handlePlayerAttack() {
    displayer.displayInputCoordinateToAttack();
    AttackResult attackResult = player.attack();
    if (attackResult == AttackResult::ShipDestroyed) {
        displayer.displayAddingAbility();
        player.getAbilityManager().addAbility();
    }
}

void Game::handlePlayerAbility() {
    player.getAbilityManager().checkAbilitiesEmpty();
    Ability* currentAbility = player.getAbilityManager().getAbility();
    if (currentAbility->getAbilityType() == AbilityType::Scanner) {
        displayer.displayInputCoordinateForScanner();
    }
    AbilityResult abilityResult = currentAbility->applyAbility(player);
    switch (abilityResult) {
        case AbilityResult::DoubleDamageSuccess:
            displayer.displayDoubleDamage();
            break;
        case AbilityResult::ScannerSuccess:
            displayer.displayScannerSuccess();
            break;
        case AbilityResult::ScannerFailure:
            displayer.displayScannerFailure();
            break;
        case AbilityResult::RandomHitShipDestroyed:
            displayer.displayAddingAbility();
            player.getAbilityManager().addAbility();
            break;
        default:
            break;
    }
}

void Game::checkGameOver() {
    if (bot.getShipManager().allShipsDestroyed() || player.getShipManager().allShipsDestroyed()) {
        gameEnded = true;
        if (player.getShipManager().allShipsDestroyed()) {
            displayer.displayFields(player.getField(), bot.getField());
            displayer.displayBotWins();

            displayer.displayNewGame();
            char choise = inputHandler.handleYesOrNo();
            switch (choise) {
                case 'N':
                case 'n':
                    gameEnded = true;
                    break;
                case 'Y':
                case 'y':
                    gameEnded = false;
                    resetGame();
                    startGame();
                    break;
                default:
                    displayer.displayIncorrectChoiсeInput();
                    break;
            }
        } else {
            displayer.displayFields(player.getField(), bot.getField());
            displayer.displayPlayerWins();

            displayer.displayContinueGame();
            char choise = inputHandler.handleYesOrNo();
            switch (choise) {
                case 'N':
                case 'n':
                    gameEnded = true;
                    break;
                case 'Y':
                case 'y':
                    gameEnded = false;
                    resetBot();
                    startGame();
                    break;
                default:
                    displayer.displayIncorrectChoiсeInput();
                    break;
            }
        }
    }
}

void Game::handleExceptions() {
    try {
        throw;
    } catch (NoAbilitiesException& exception) {
        displayer.displayException(exception);
    } catch (OutOfBoundsException& exception) {
        displayer.displayException(exception);
    } catch (AlreadyAttackedCellException& exception) {
        displayer.displayException(exception);
    } catch (SaveFileHashMismatchException(exception)) {
        displayer.displayException(exception);
    }
}

void Game::resetBot() {
    Field newField = Field(10, 10);
    ShipManager newShips = ShipManager();

    for (auto* ship : newShips.getShips()) {
        newField.placeShipRandomly(ship);
    }

    bot.setField(newField);
    bot.setShipManager(newShips);
}

void Game::resetGame() {
    resetBot();

    Field newField = Field(10, 10);
    ShipManager newShips = ShipManager();
    AbilityManager newAbilities = AbilityManager();

    player.setField(newField);
    player.setShipManager(newShips);
    player.setAbilityManager(newAbilities);
}
