#include "../include/UnableToOpenFileException.hpp"

UnableToOpenFileException::UnableToOpenFileException() {
    message = "Unable to open file!";
}

const char* UnableToOpenFileException::what() const noexcept {
    return message.c_str();
}
