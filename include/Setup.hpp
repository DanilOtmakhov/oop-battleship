#ifndef SETUP_HPP
#define SETUP_HPP

#include "InputHandler.hpp"
#include "Deserialization.hpp"
#include "FileWrapper.hpp"

class Setup {
    private:
        InputHandler& inputHandler;
    public:
        Setup(InputHandler& inputHandler) : inputHandler(inputHandler) {};
        void deserializeSetup() {
            nlohmann::json j;
            FileWrapper fileWrapper = FileWrapper("/Users/danilotmakhov/Documents/studies/oop/battleship/setup.json");
            std::map<char, Command> newCommands;
            fileWrapper.read(j);
            Deserialization(j).from_json(newCommands);
            inputHandler.setCommands(newCommands);
        }
};

#endif
