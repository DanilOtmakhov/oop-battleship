#include "../include/Game.hpp"


void Game::startGame() {
    ConsoleDisplayer displayer;
    InputHandler inputHandler;
    Field gamefield = Field(10, 10);
    Field enemyGamefield = Field(10, 10);
    ShipManager ships = ShipManager();
    ShipManager enemyShips = ShipManager();
    AbilityManager abilities = AbilityManager();
    AbilityManager enemyAbilities = AbilityManager();
    Player player = Player(gamefield, ships, abilities);
    Player enemyPlayer = Player(enemyGamefield, enemyShips, enemyAbilities);
    player.setEnemyPlayer(enemyPlayer);
    enemyPlayer.setEnemyPlayer(player);

    ships.getShip(0)->changeOrientaion(true);
    ships.getShip(1)->changeOrientaion(true);

    gamefield.placeShip(ships.getShip(0), true, {7, 0});
    gamefield.placeShip(ships.getShip(1), true, {0, 7});
    gamefield.placeShip(ships.getShip(2), false, {3, 1});
    gamefield.placeShip(ships.getShip(3), false, {3, 4});
    gamefield.placeShip(ships.getShip(4), false, {2, 6});
    gamefield.placeShip(ships.getShip(5), false, {7, 6});
    gamefield.placeShip(ships.getShip(6), false, {8, 9});
    gamefield.placeShip(ships.getShip(7), false, {4, 8});
    gamefield.placeShip(ships.getShip(8), false, {1, 3});
    gamefield.placeShip(ships.getShip(9), false, {0, 0});

    enemyShips.getShip(0)->changeOrientaion(true);
    enemyShips.getShip(1)->changeOrientaion(true);

    enemyGamefield.placeShip(enemyShips.getShip(0), true, {7, 0});
    enemyGamefield.placeShip(enemyShips.getShip(1), true, {0, 7});
    enemyGamefield.placeShip(enemyShips.getShip(2), false, {3, 1});
    enemyGamefield.placeShip(enemyShips.getShip(3), false, {3, 4});
    enemyGamefield.placeShip(enemyShips.getShip(4), false, {2, 6});
    enemyGamefield.placeShip(enemyShips.getShip(5), false, {7, 6});
    enemyGamefield.placeShip(enemyShips.getShip(6), false, {8, 9});
    enemyGamefield.placeShip(enemyShips.getShip(7), false, {4, 8});
    enemyGamefield.placeShip(enemyShips.getShip(8), false, {1, 3});
    enemyGamefield.placeShip(enemyShips.getShip(9), false, {0, 0});

    displayer.displayFields(gamefield, enemyGamefield);

    while (!enemyShips.allShipsDestroyed()) {
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
                        abilities.addAbility();
                    }
                    break;
                }
                case 2: {
                    abilities.checkAbilitiesEmpty();
                    Ability* currentAbility = abilities.getAbility();
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
                        abilities.addAbility();
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
        displayer.displayFields(gamefield, enemyGamefield);
    }
}
