#ifndef RANDOM_HIT_ABILITY_HPP
#define RANDOM_HIT_ABILITY_HPP

#include "Ability.hpp"
#include "Player.hpp"
#include <algorithm>

class RandomHitAbility : public Ability {
    public:
        AbilityResult applyAbility(Player& player) override;
        AbilityType getAbilityType() override;
};

#endif
