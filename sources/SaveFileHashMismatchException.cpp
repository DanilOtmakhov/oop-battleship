#include "../include/SaveFileHashMismatchException.hpp"

SaveFileHashMismatchException::SaveFileHashMismatchException() {
    message = "Invalid save file data!";
}

const char* SaveFileHashMismatchException::what() const noexcept {
    return message.c_str();
}
