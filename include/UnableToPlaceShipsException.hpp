#ifndef UNABLE_TO_PLACE_SHIPS_EXCEPTION_HPP
#define UNABLE_TO_PLACE_SHIPS_EXCEPTION_HPP

#include <exception>
#include <string>

class UnableToPlaceShipsException : public std::exception {
private:
    std::string message;

public:
    UnableToPlaceShipsException();
    virtual const char* what() const noexcept override;
};

#endif
