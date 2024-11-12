#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <iostream>
#include "Structs.hpp"


class InputHandler {
    public:
        int handleAttackOrApplyAbilityInput();
        Coordinate handleCoordinateInput();
};

#endif
