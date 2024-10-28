#include "../include/Abilities.hpp"


DoubleDamageAbility::DoubleDamageAbility(Field& field, Coordinate coordinate) : field(field), coordinate(coordinate) {}

ScannerAbility::ScannerAbility(Field& field, Coordinate coordinate) : field(field), coordinate(coordinate) {}

RandomHitAbility::RandomHitAbility(Field& field) : field(field) {}

void DoubleDamageAbility::apply_ability() {

}

void ScannerAbility::apply_ability() {

}

void RandomHitAbility::apply_ability() {

}
