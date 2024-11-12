#include "../include/OutOfBoundsException.hpp"

OutOfBoundsException::OutOfBoundsException() {
    message = "Coordinates out of bounds!";
}

const char* OutOfBoundsException::what() const noexcept {
    return message.c_str();
}
