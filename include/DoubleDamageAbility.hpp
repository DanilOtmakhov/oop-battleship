#ifndef DOUBLE_DAMAGE_ABILITY_HPP
#define DOUBLE_DAMAGE_ABILITY_HPP

#include "Ability.hpp"
#include "Player.hpp"


class DoubleDamageAbility : public Ability {
    public:
        AbilityResult applyAbility(Player& player) override;
        AbilityType getAbilityType() override;
};

#endif
