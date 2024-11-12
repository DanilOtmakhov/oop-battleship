#include "../include/NoAbilitiesException.hpp"

NoAbilitiesException::NoAbilitiesException() {
    message = "You have no abilities! To get the ability, you need to destroy the ship.";
}

const char* NoAbilitiesException::what() const noexcept {
    return message.c_str();
}
