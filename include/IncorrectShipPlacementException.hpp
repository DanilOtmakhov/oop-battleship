#ifndef INCORRECT_SHIP_PLACEMENT_HPP
#define INCORRECT_SHIP_PLACEMENT_HPP

#include <exception>
#include <string>

class IncorrectShipPlacementException : public std::exception {
private:
    std::string message;

public:
    IncorrectShipPlacementException();
    virtual const char* what() const noexcept override;
};

#endif
