#include "../include/ShipManager.hpp"


ShipManager::ShipManager(int number, std::vector<int> lengths) {
    for (int i = 0; i < number; i++) {
        if (lengths[i] < 1 || lengths[i] > 4) {
            throw std::invalid_argument("Length of ship must be between 1 and 4");
        }
        ships.push_back(Ship(lengths[i]));
    }
}

ShipManager::ShipManager() : ShipManager(10, {4, 3, 3, 2, 2, 2, 1, 1, 1, 1}) {}

std::vector<Ship*> ShipManager::getShips() {
    std::vector<Ship*> shipPointers;
    for (int i = 0; i < ships.size(); i++) {
        shipPointers.push_back(&ships[i]);
    }
    return shipPointers;
}

void ShipManager::addShip(int length) {
    ships.push_back(Ship(length));
}
