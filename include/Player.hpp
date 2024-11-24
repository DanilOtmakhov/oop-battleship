#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "IPlayer.hpp"

class AbilityManager;

class Player {
    private:
        Field& field;
        ShipManager& ships;
        AbilityManager& abilities;
        Player* enemy;
        int damage = 1;
    public:
        Player(Field& field, ShipManager& ships, AbilityManager& abilities);
        void setDamage(int newDamage);
        Field& getField();
        std::vector <Ship*> getShips();
        ShipManager& getShipManager();
        AbilityManager& getAbilityManager();
        Player* getEnemyPointer();
        void setEnemyPlayer(Player player);
        AttackResult attack();
};

#endif
