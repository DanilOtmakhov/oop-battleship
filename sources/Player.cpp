#include "../include/Player.hpp"


Player::Player(Field& field, ShipManager& shipManager, AbilityManager& abilityManager)
    : IPlayer(field, shipManager), abilityManager(abilityManager) {}

void Player::setDamage(int newDamage) {
    damage = newDamage;
}

AbilityManager& Player::getAbilityManager() {
    return abilityManager;
}

AttackResult Player::attack() {
    InputHandler inputHandler;
    Coordinate coordinate = inputHandler.handleCoordinateInput();
    AttackResult attackResult = enemy->getField().handleAttack(coordinate, damage);
    setDamage(1);
    return attackResult;
}

void Player::setAbilityManager(AbilityManager& newAbilityManager) {
    abilityManager = newAbilityManager;
}
