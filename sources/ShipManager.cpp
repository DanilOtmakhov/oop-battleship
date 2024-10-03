#include "../include/ShipManager.hpp"


ShipManager::ShipManager(int number, std::vector<int> lengths) {
    for (int i = 0; i < number; i++) {
        if (lengths[i] < 1 || lengths[i] > 4) {
            throw std::invalid_argument("Length of ship must be between 1 and 4");
        }
        ships.push_back(new Ship(lengths[i]));
    }
}


