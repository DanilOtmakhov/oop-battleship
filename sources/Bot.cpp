#include "../include/Bot.hpp"

Bot::Bot(Field& field, ShipManager& ships) : IPlayer(field, ships) {}

AttackResult Bot::attack() {
    AttackResult attackResult = enemy->getField().handleRandomAttack();
    return attackResult;
}
