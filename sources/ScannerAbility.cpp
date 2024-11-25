#include "../include/ScannerAbility.hpp"


AbilityResult ScannerAbility::applyAbility(Player& player) {
    InputHandler inputHandler;
    IPlayer* enemyPlayer = player.getEnemyPointer();
    Coordinate selectedCoordinate = inputHandler.handleCoordinateInput();
    for (int y = selectedCoordinate.y; y <= selectedCoordinate.y + 1; y++) {
        for (int x = selectedCoordinate.x; x <= selectedCoordinate.x + 1; x++) {
            if (!enemyPlayer->getField().isCoordinateCorrect(selectedCoordinate)) {
                throw OutOfBoundsException();
            }
            if (enemyPlayer->getField().isShipInCell({x, y}) && enemyPlayer->getField().getCellValue({x, y}) != CellValue::Destroyed) {
                return AbilityResult::ScannerSuccess;
            }
        }
    }

    return AbilityResult::ScannerFailure;
}

AbilityType ScannerAbility::getAbilityType() {
    return AbilityType::Scanner;
}
