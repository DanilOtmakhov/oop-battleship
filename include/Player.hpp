#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "IPlayer.hpp"
#include "AbilityManager.hpp"
class AbilityManager;

class Player: public IPlayer {
    private:
        AbilityManager& abilityManager;
        int damage = 1;
    public:
        Player(Field& field, ShipManager& shipManager, AbilityManager& abilityManager);
        void setDamage(int newDamage);
        AbilityManager& getAbilityManager();
        AttackResult attack() override;
};

#endif
