#ifndef BOT_HPP
#define BOT_HPP

#include "IPlayer.hpp"

class Bot: public IPlayer {
    public:
        Bot(Field field, ShipManager shipManager);
        AttackResult attack();
};

#endif
