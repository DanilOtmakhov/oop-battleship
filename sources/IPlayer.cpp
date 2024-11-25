#include "../include/IPlayer.hpp"

IPlayer::IPlayer(Field& field, ShipManager& shipManager) : field(field), shipManager(shipManager) {}

Field& IPlayer::getField() {
    return field;
}

void IPlayer::setEnemy(IPlayer* enemy) {
    this->enemy = enemy;
}

IPlayer* IPlayer::getEnemyPointer() {
    return enemy;
}

ShipManager& IPlayer::getShipManager() {
    return shipManager;
}
