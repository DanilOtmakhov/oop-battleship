#include "../include/Game.hpp"

void Game::startGame() {

    // ConsoleDisplayer displayer;
    // InputHandler inputHandler;

    Field field = Field(10, 10);
    ShipManager shipManager = ShipManager();
    AbilityManager abilityManager = AbilityManager();

    Field botField = Field(10, 10);
    ShipManager botShipManager = ShipManager();

    Player player = Player(field, shipManager, abilityManager);
    Bot bot = Bot(botField, botShipManager);

    player.setEnemy(&bot);
    bot.setEnemy(&player);

    shipManager.getShip(0)->changeOrientaion(true);
    shipManager.getShip(1)->changeOrientaion(true);

    field.placeShip(shipManager.getShip(0), true, {7, 0});
    field.placeShip(shipManager.getShip(1), true, {0, 7});
    field.placeShip(shipManager.getShip(2), false, {3, 1});
    field.placeShip(shipManager.getShip(3), false, {3, 4});
    field.placeShip(shipManager.getShip(4), false, {2, 6});
    field.placeShip(shipManager.getShip(5), false, {7, 6});
    field.placeShip(shipManager.getShip(6), false, {8, 9});
    field.placeShip(shipManager.getShip(7), false, {4, 8});
    field.placeShip(shipManager.getShip(8), false, {1, 3});
    field.placeShip(shipManager.getShip(9), false, {0, 0});

    botShipManager.getShip(0)->changeOrientaion(true);
    botShipManager.getShip(1)->changeOrientaion(true);

    botField.placeShip(botShipManager.getShip(0), true, {7, 0});
    botField.placeShip(botShipManager.getShip(1), true, {0, 7});
    botField.placeShip(botShipManager.getShip(2), false, {3, 1});
    botField.placeShip(botShipManager.getShip(3), false, {3, 4});
    botField.placeShip(botShipManager.getShip(4), false, {2, 6});
    botField.placeShip(botShipManager.getShip(5), false, {7, 6});
    botField.placeShip(botShipManager.getShip(6), false, {8, 9});
    botField.placeShip(botShipManager.getShip(7), false, {4, 8});
    botField.placeShip(botShipManager.getShip(8), false, {1, 3});
    botField.placeShip(botShipManager.getShip(9), false, {0, 0});

    displayer.displayFields(field, botField);

    while (!bot.getShipManager().allShipsDestroyed() && !player.getShipManager().allShipsDestroyed()) {
        displayer.displayAttackOrApplyAbility();
        int playerChoise = inputHandler.handleAttackOrApplyAbilityInput();
        try {
            switch (playerChoise) {
                AttackResult attackResult;
                case 1: {
                    displayer.displayInputCoordinateToAttack();
                    attackResult = player.attack();
                    if (attackResult == AttackResult::ShipDestroyed) {
                        displayer.displayAddingAbility();
                        player.getAbilityManager().addAbility();
                    }
                    break;
                }
                case 2: {
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
                    break;
                }
                default:
                    displayer.displayIncorrectChoiсeInput();
                    continue;
                    break;
            }
        }
        catch (NoAbilitiesException& exception) {
            displayer.displayException(exception);
            continue;
        }
        catch (OutOfBoundsException& exception) {
            displayer.displayException(exception);
            continue;
        }
        catch (AlreadyAttackedCellException& exception) {
            displayer.displayException(exception);
            continue;
        }
        bot.attack();
        displayer.displayFields(field, botField);
    }
}


void Game::gameRound() {

}

void Game::gameOver() {

}

void Game::saveGame() {

}

void Game::loadGame() {

}
