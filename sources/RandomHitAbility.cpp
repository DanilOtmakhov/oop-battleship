#include "../include/RandomHitAbility.hpp"


AbilityResult RandomHitAbility::applyAbility(Player& player) {
    IPlayer* enemyPlayer = player.getEnemyPointer();
    std::vector <Coordinate> availableCoordinatesToAttack;

    std::vector <Ship*> ships = enemyPlayer->getShipManager().getShips();
    std::vector <Ship*> aliveShips;

    auto isAlive = [](Ship* ship) {
        return ship->getStatus() == ShipStatus::Untouched || ship->getStatus() == ShipStatus::Damaged;
    };

    std::copy_if(ships.begin(), ships.end(), std::back_inserter(aliveShips), isAlive);

    if (!aliveShips.empty()) {
        for (auto* ship : aliveShips) {
            for (int i = 0; i < ship->getLength(); i++) {
                if (ship->getSegmentStatusByIndex(i) == SegmentStatus::Untouched || ship->getSegmentStatusByIndex(i) == SegmentStatus::Damaged) {
                    availableCoordinatesToAttack.push_back(ship->getSegmentCoordinateByIndex(i));
                }
            }
        }
        int randomIndex = rand() % availableCoordinatesToAttack.size();
        AttackResult attackResult = enemyPlayer->getField().handleAttack(availableCoordinatesToAttack[randomIndex]);
        if (attackResult == AttackResult::ShipDestroyed) {
            return AbilityResult::RandomHitShipDestroyed;
        }
        return AbilityResult::RandomHitSuccess;
    }

    return AbilityResult::RandomHitFailure;
}

AbilityType RandomHitAbility::getAbilityType() {
    return AbilityType::RandomHit;
}
