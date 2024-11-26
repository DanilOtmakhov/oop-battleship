#include "../include/Game.hpp"

Game::Game(Player player, Bot bot) : player(player), bot(bot) {}

void Game::startGame() {

    displayer.displayFields(player.getField(), bot.getField());

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
        displayer.displayFields(player.getField(), bot.getField());
    }
}


void Game::gameRound(int playerChoise) {

}

void Game::gameOver() {

}
