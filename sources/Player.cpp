#include "../include/Player.hpp"


Player::Player(Field& field, ShipManager& ships, AbilityManager& abilities) : field(field), ships(ships), abilities(abilities) {}

void Player::setDamage(int newDamage) {
    damage = newDamage;
}

Field& Player::getField() {
    return field;
}

std::vector <Ship*> Player::getShips() {
    return ships.getShips();
}

ShipManager& Player::getShipManager() {
    return ships;
}

AbilityManager& Player::getAbilityManager() {
    return abilities;
}

Player* Player::getEnemyPointer() {
    return enemy;
}

void Player::setEnemyPlayer(Player player) {
    enemy = &player;
}

AttackResult Player::attack() {
    InputHandler inputHandler;
    Coordinate coordinate = inputHandler.handleCoordinateInput();
    AttackResult attackResult = enemy->getField().handleAttack(coordinate, damage);
    setDamage(1);
    return attackResult;
}
