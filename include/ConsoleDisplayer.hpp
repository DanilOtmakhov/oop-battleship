#ifndef CONSOLE_DISPLAYER_HPP
#define CONSOLE_DISPLAYER_HPP

#include <iostream>
#include <map>
#include "Field.hpp"
#include "Command.hpp"


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
        void displayInputCoordinateToAttack();
        void displaySymbolsOfCells();
        void displayDoubleDamage();
        void displayInputCoordinateForScanner();
        void displayScannerSuccess();
        void displayScannerFailure();
        void displayAddingAbility();
        void displayException(std::exception& exception);
        void displayGameStartInfo(const std::map<char, Command>& commands);
        void displayBotWins();
        void displayPlayerWins();
        void displaySavingGame();
        void displayLoadingGame();
        void displayContinueGame();
        void displayNewGame();
        void displayInfo(const std::map<char, Command>& commands);
        void displayIncorrectCommandInput();
        void displayAbilityUsed();
        void displaySaveFinished();
        void displayLoadFinished();
        void displayRoundCompleted();
};

#endif
