#ifndef SCANNER_ABILITY_HPP
#define SCANNER_ABILITY_HPP

#include "Ability.hpp"
#include "Player.hpp"


class ScannerAbility : public Ability {
    public:
        AbilityResult applyAbility(Player& player) override;
        AbilityType getAbilityType() override;
};

#endif
