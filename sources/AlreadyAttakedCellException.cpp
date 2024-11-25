#include "../include/AlreadyAttackedCellException.hpp"

AlreadyAttackedCellException::AlreadyAttackedCellException() {
    message = "This cell is already attacked!";
}

const char* AlreadyAttackedCellException::what() const noexcept {
    return message.c_str();
}
