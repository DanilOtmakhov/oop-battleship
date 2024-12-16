#ifndef SHIP_MANAGER
#define SHIP_MANAGER

#include <iostream>
#include <vector>
#include "Ship.hpp"


class ShipManager {
    private:
        std::vector <Ship*> ships;
    public:
        ShipManager(int number, std::vector<int> lengths);
        ShipManager();
        std::vector <Ship*> getShips();
        Ship* getShip(int index);
        bool allShipsDestroyed();
        void addShip(Ship* ship);
};

#endif
