#include "../include/ShipManager.hpp"


ShipManager::ShipManager(int number, std::vector<int> lengths) {
    for (int i = 0; i < number; i++) {
        if (lengths[i] < 1 || lengths[i] > 4) {
            throw std::invalid_argument("Length of ship must be between 1 and 4");
        }
        ships.push_back(new Ship(lengths[i]));
    }
}

ShipManager::ShipManager() : ShipManager(10, {4, 3, 3, 2, 2, 2, 1, 1, 1, 1}) {}

ShipManager::~ShipManager() {
    for (auto& ship : this->ships) {
        delete ship;
    }
}

std::vector<Ship*> ShipManager::getShips() {
    return this->ships;
}

void ShipManager::addShip(int length) {
    ships.push_back(new Ship(length));
}
