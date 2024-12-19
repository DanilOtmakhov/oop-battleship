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
    Command command = inputHandler.handleCommandInput();
    switch (command) {
        case Command::info:
            displayer.displayInfo();
            break;
        case Command::start:
            startGame();
            break;
        case Command::save:
            displayer.displaySavingGame();
            saveGame();
            startGame();
            break;
        case Command::load:
            displayer.displayLoadingGame();
            loadGame();
            displayer.displayFields(player.getField(), bot.getField());
            initializeGame();
            break;
        case Command::quit:
            gameEnded = true;
            break;
        default:
            displayer.displayIncorrectCommandInput();
            break;
    }
}

void Game::playerTurn() {
    displayer.displayAttackOrApplyAbility();
    Command command = inputHandler.handleCommandInput();
    try {
        switch (command) {
            case Command::attack:
                handlePlayerAttack();
                break;
            case Command::ability:
                handlePlayerAbility();
                break;
            case Command::save:
                displayer.displaySavingGame();
                saveGame();
                playerTurn();
                break;
            case Command::load:
                displayer.displayLoadingGame();
                loadGame();
                displayer.displayFields(player.getField(), bot.getField());
                playerTurn();
                break;
            case Command::quit:
                gameEnded = true;
                break;
            default:
                displayer.displayIncorrectCommandInput();
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
                    displayer.displayIncorrectCommandInput();
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
                    displayer.displayIncorrectCommandInput();
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

void Game::saveGame() {
    gameState.saveGame("/Users/danilotmakhov/Desktop/oop/battleship/saveFile.json");
}

void Game::loadGame() {
    try {
        gameState.loadGame("/Users/danilotmakhov/Desktop/oop/battleship/saveFile.json");
    } catch (SaveFileHashMismatchException(exception)) {
        displayer.displayException(exception);
    } catch (nlohmann::json::parse_error(exception)) {
        displayer.displayException(exception);
    }
}
