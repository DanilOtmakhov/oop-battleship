#include "../include/IPlayer.hpp"

IPlayer::IPlayer(Field field, ShipManager shipManager) : field(field), shipManager(shipManager) {}

void IPlayer::setEnemy(IPlayer* enemy) {
    enemy = enemy;
}

IPlayer* IPlayer::getEnemyPointer() {
    return enemy;
}

ShipManager& IPlayer::getShipManager() {
    return shipManager;
}
