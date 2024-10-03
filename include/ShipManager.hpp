#ifndef SHIP_MANAGER
#define SHIP_MANAGER

#include <iostream>
#include <vector>
#include "Ship.hpp"


class ShipManager {
    private:
        std::vector<Ship*> ships;
    public:
        ShipManager(int number, std::vector<int> lengths = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1});

};

#endif
