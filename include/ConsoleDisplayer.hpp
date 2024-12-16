#ifndef CONSOLE_DISPLAYER_HPP
#define CONSOLE_DISPLAYER_HPP

#include <iostream>
#include "Field.hpp"


class ConsoleDisplayer {
    private:
        struct Colors {
            const std::string white = "\033[97m";
            const std::string blue = "\033[36m";
            const std::string red = "\033[91m";
            const std::string yellow = "\033[33m";
            const std::string reset = " \033[0m";
        };

    public:
        void displayField(Field field, bool isEnemy);
        void displayFields(Field field, Field field2);
        void displayAttackOrApplyAbility();
        void displayInputCoordinateToAttack();
        void displaySymbolsOfCells();
        void displayDoubleDamage();
        void displayInputCoordinateForScanner();
        void displayScannerSuccess();
        void displayScannerFailure();
        void displayIncorrectChoiсeInput();
        void displayAddingAbility();
        void displayException(std::exception& exception);
        void displayGameStart();
        void displayBotWins();
        void displayPlayerWins();
        void displaySavingGame();
        void displayLoadingGame();
        void displayContinueGame();
        void displayNewGame();
};

#endif
