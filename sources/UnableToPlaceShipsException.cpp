#include "../include/UnableToPlaceShipsException.hpp"

UnableToPlaceShipsException::UnableToPlaceShipsException() {
    message = "Unable to place ships!";
}

const char* UnableToPlaceShipsException::what() const noexcept {
    return message.c_str();
}
