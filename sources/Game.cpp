#include "../include/Game.hpp"

Game::Game(Player player, Bot bot, GameState gameState, ConsoleDisplayer displayer) : player(player), bot(bot), gameState(gameState), displayer(displayer) {}

void Game::botTurn() {
    try {
        bot.attack();
    } catch (...) {
        handleExceptions();
        botTurn();
    }
    for (const auto& observer : this->observers) {
        observer->roundCompleted();
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
    for (const auto& observer : this->observers) {
        observer->abilityUsed();
    }
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
    gameState.saveGame("/Users/danilotmakhov/Documents/studies/oop/battleship/saveFile.json");
    for (const auto& observer : this->observers) {
        observer->saveSuccess();
    }
}

void Game::loadGame() {
    try {
        gameState.loadGame("/Users/danilotmakhov/Documents/studies/oop/battleship/saveFile.json");
    } catch (SaveFileHashMismatchException(exception)) {
        displayer.displayException(exception);
    } catch (nlohmann::json::parse_error(exception)) {
        displayer.displayException(exception);
    }
}

GameState& Game::getGameState() {
    return gameState;
}

bool Game::isGameOver() {
        if (bot.getShipManager().allShipsDestroyed()) {
            for (const auto& observer : this->observers) {
                observer->playerWin();
            }
        } else if (player.getShipManager().allShipsDestroyed()) {
            for (const auto& observer : this->observers) {
                observer->botWin();
            }
        }
        return bot.getShipManager().allShipsDestroyed() || player.getShipManager().allShipsDestroyed();
    }

bool Game::isPlayerDefeated() {
    return player.getShipManager().allShipsDestroyed();
}

void Game::addObserver(GameObserver* observer) {
    if (observer != nullptr) {
        observers.push_back(observer);
    }
}
