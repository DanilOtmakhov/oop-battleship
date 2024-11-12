#include "../include/IncorrectShipPlacementException.hpp"

IncorrectShipPlacementException::IncorrectShipPlacementException() {
    message = "Incorrect placement of the ship!";
}

const char* IncorrectShipPlacementException::what() const noexcept {
    return message.c_str();
}
