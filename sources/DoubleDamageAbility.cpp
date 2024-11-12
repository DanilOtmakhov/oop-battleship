#include "../include/DoubleDamageAbility.hpp"


AbilityResult DoubleDamageAbility::applyAbility(Player& player) {
    player.setDamage(2);
    return AbilityResult::DoubleDamageSuccess;
}

AbilityType DoubleDamageAbility::getAbilityType() {
    return AbilityType::DoubleDamage;
}
