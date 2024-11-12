#ifndef ABILITY_HPP
#define ABILITY_HPP

#include "Field.hpp"
class Player;


enum class AbilityType {
    DoubleDamage,
    Scanner,
    RandomHit
};

enum class AbilityResult {
    DoubleDamageSuccess,
    ScannerSuccess,
    ScannerFailure,
    RandomHitSuccess,
    RandomHitShipDestroyed,
    RandomHitFailure
};

class Ability {
    public:
        virtual ~Ability() = default;
        virtual AbilityResult applyAbility(Player& player) = 0;
        virtual AbilityType getAbilityType() = 0;
};

#endif
