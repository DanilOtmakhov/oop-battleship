#ifndef IPLAYER_HPP
#define IPLAYER_HPP

#include "Field.hpp"
#include "ShipManager.hpp"
#include "InputHandler.hpp"

class IPlayer {
    private:
        Field& field;
        ShipManager shipManager;
        IPlayer* enemy;
    public:
        IPlayer(Field field, ShipManager shipManager);
        virtual ~IPlayer() {};
        void setEnemy(IPlayer* enemy);
        IPlayer* getEnemyPointer();
        ShipManager& getShipManager();
        virtual AttackResult attack() = 0;
};

#endif
