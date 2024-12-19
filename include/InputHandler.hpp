#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <iostream>
#include <map>
#include "Structs.hpp"
#include "Command.hpp"


class InputHandler {
    private:
        std::map <char, Command> commands;
    public:
        InputHandler();
        Command handleCommandInput();
        Coordinate handleCoordinateInput();
        char handleYesOrNo();
        void setCommands(std::map <char, Command> newCommands);
};

#endif
