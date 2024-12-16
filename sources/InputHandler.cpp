#include "../include/InputHandler.hpp"


int InputHandler::handleChoise() {
    int choice;
    std::cin >> choice;
    return choice;
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
