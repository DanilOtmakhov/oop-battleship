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

std::vector <Ship*> ShipManager::getShips() {
    return ships;
}

Ship* ShipManager::getShip(int index) {
    if (index < 0 || index >= ships.size()) {
        throw std::out_of_range("Invalid index!");
    }
    return ships[index];
}

bool ShipManager::allShipsDestroyed() {
    for (auto* ship : ships) {
        if (ship->getStatus() != ShipStatus::Destroyed) {
            return false;
        }
    }
    return true;
}
