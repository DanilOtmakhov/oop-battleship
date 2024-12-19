#include "../include/InputHandler.hpp"

InputHandler::InputHandler() {
    commands = {
        {'i', Command::info},
        {'g', Command::start},
        {'a', Command::attack},
        {'b', Command::ability},
        {'l', Command::load},
        {'s', Command::save},
        {'q', Command::quit}
    };
}

Command InputHandler::handleCommandInput() {
    std::string line;
    std::cin >> line;
    if (line.size() == 1 && this->commands.find(line[0]) != this->commands.end()) {
        return commands[line[0]];
    }
    return Command::info;
}

Coordinate InputHandler::handleCoordinateInput() {
    char x_char;
    int y;

    std::cin >> x_char >> y;

    x_char = std::toupper(x_char);
    int x = x_char - 'A';

    return Coordinate{x, y - 1};
}

char InputHandler::handleYesOrNo() {
    char choise;
    std::cin >> choise;

    return choise;
}

void InputHandler::setCommands(std::map <char, Command> newCommands) {
    commands = newCommands;
}
