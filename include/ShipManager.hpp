#ifndef SHIP_MANAGER
#define SHIP_MANAGER

#include <iostream>
#include <vector>
#include "Ship.hpp"


class ShipManager {
    private:
        std::vector<Ship*> ships;
    public:
        ShipManager(int number, std::vector<int> lengths);
        ShipManager();
        ~ShipManager();
        std::vector<Ship*> getShips();
        void addShip(int length);
};

#endif
