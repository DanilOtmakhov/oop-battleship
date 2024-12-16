#include "../include/ConsoleDisplayer.hpp"

void ConsoleDisplayer::displayField(Field field, bool isEnemy) {
    int rows = field.getRows();
    int columns = field.getColumns();
    Colors colors;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            std::cout << colors.white << "+---";
        }
        std::cout << colors.white << "+" << colors.reset << std::endl;
        for (int k = 0; k < columns; k++) {
            std::cout << colors.white << "|";
            CellValue value = field.getCellValue({k, i});
            switch (value) {
                case CellValue::Hidden:
                    std::cout << ' ' << static_cast<char>(value) << ' ';
                    break;
                case CellValue::Revealed:
                    std::cout << colors.blue << ' ' << static_cast<char>(value) << ' ';
                    break;
                case CellValue::ShipPart:
                    if (isEnemy) {
                        std::cout << colors.yellow << ' ' << static_cast<char>(CellValue::Hidden) << ' ';
                        break;
                    }
                    std::cout << colors.yellow << ' ' << static_cast<char>(value) << ' ';
                    break;
                case CellValue::Damaged:
                    std::cout << colors.red << ' ' << static_cast<char>(value) << ' ';
                    break;
                case CellValue::Destroyed:
                    std::cout << colors.red << ' ' << static_cast<char>(value) << ' ';
                    break;
            }
        }
        std::cout << colors.white << "|" << colors.reset << std::endl;
    }
    for (int j = 0; j < columns; j++) {
        std::cout << colors.white << "+---";
    }
    std::cout << colors.white << "+" << colors.reset << std::endl;
}

void ConsoleDisplayer::displayFields(Field field1, Field field2) {
    int rows = field1.getRows();
    int columns = field1.getColumns();
    Colors colors;
    std::cout << "    ";
    for (int j = 0; j < columns; j++) {
        if (j == 0) {
            std::cout << colors.white << " " << char('A' + j) << "   ";
        } else {
            std::cout << colors.white << "" << char('A' + j) << "   ";
        }
    }
    std::cout << colors.reset << "   ";

    for (int j = 0; j < columns; j++) {
        std::cout << colors.white << " " << char('A' + j) << "  ";
    }
    std::cout << colors.reset << std::endl;

    for (int i = 0; i < rows; i++) {
        std::cout << "  ";
        for (int j = 0; j < columns; j++) {
            if (j == 0) {
                std::cout << colors.white << " +---";
            } else {
                std::cout << colors.white << "+---";
            }
        }
        std::cout << colors.white << "+" << colors.reset << "   ";

        for (int j = 0; j < columns; j++) {
            std::cout << colors.white << "+---";
        }
        std::cout << colors.white << "+" << colors.reset << std::endl;

        if (i == 9) {
            std::cout << colors.white << (i + 1) << " ";
        } else {
            std::cout << colors.white << " " << (i + 1) << " ";
        }
        for (int k = 0; k < columns; k++) {
            std::cout << colors.white << "|";
            CellValue value1 = field1.getCellValue({k, i});
            switch (value1) {
                case CellValue::Hidden:
                    std::cout << ' ' << static_cast<char>(value1) << ' ';
                    break;
                case CellValue::Revealed:
                    std::cout << colors.blue << ' ' << static_cast<char>(value1) << ' ';
                    break;
                case CellValue::ShipPart:
                    std::cout << colors.yellow << ' ' << static_cast<char>(value1) << ' ';
                    break;
                case CellValue::Damaged:
                case CellValue::Destroyed:
                case CellValue::ShipDestroyed:
                    std::cout << colors.red << ' ' << static_cast<char>(value1) << ' ';
                    break;
            }
        }
        if (i == 9) {
            std::cout << colors.white << "|" << colors.reset << "" << (i + 1) << " ";
        } else {
            std::cout << colors.white << "|" << colors.reset << " " << (i + 1) << " ";
        }

        for (int k = 0; k < columns; k++) {
            std::cout << colors.white << "|";
            CellValue value2 = field2.getCellValue({k, i});
            switch (value2) {
                case CellValue::Hidden:
                    std::cout << ' ' << static_cast<char>(value2) << ' ';
                    break;
                case CellValue::Revealed:
                    std::cout << colors.blue << ' ' << static_cast<char>(value2) << ' ';
                    break;
                case CellValue::ShipPart:
                    //std::cout << colors.yellow << ' ' << static_cast<char>(value2) << ' ';
                    std::cout << colors.yellow << ' ' << static_cast<char>(CellValue::Hidden) << ' ';
                    break;
                case CellValue::Damaged:
                case CellValue::Destroyed:
                case CellValue::ShipDestroyed:
                    std::cout << colors.red << ' ' << static_cast<char>(value2) << ' ';
                    break;
            }
        }
        std::cout << colors.white << "|" << colors.reset << std::endl;
    }

    std::cout << colors.white << "   ";
    for (int j = 0; j < columns; j++) {
        std::cout << colors.white << "+---";
    }
    std::cout << colors.white << "+" << colors.reset << "   ";

    for (int j = 0; j < columns; j++) {
        std::cout << colors.white << "+---";
    }
    std::cout << colors.white << "+" << colors.reset << std::endl;
}

void ConsoleDisplayer::displaySymbolsOfCells() {
    Colors colors;
    std::cout << colors.white << "Symbols of cells:" << std::endl;
    std::cout << colors.blue << static_cast<char>(CellValue::Revealed) << colors.white << " - missed attack;" << std::endl;
    std::cout << colors.yellow << static_cast<char>(CellValue::ShipPart) << colors.white << " - untouched segment of the ship;" << std::endl;
    std::cout << colors.red << static_cast<char>(CellValue::Damaged) << colors.white << " - damaged segment of the ship;" << std::endl;
    std::cout << colors.red << static_cast<char>(CellValue::Destroyed) << colors.white << " - destroyed ship segment." << colors.reset << std::endl;
}

void ConsoleDisplayer::displayAttackOrApplyAbility() {
    std::cout << "Attack - 1\nUse ability - 2\nSave Game - 3\nLoad Game - 4\nQuit Game - 5" << std::endl;
}

void ConsoleDisplayer::displayInputCoordinateToAttack() {
    std::cout << "Enter coordinates for attack:" << std::endl;
}

void ConsoleDisplayer::displayDoubleDamage() {
    std::cout << "Double damage in the next attack." << std::endl;
}

void ConsoleDisplayer::displayInputCoordinateForScanner() {
    std::cout << "Enter the coordinates to use scanner:" << std::endl;
}

void ConsoleDisplayer::displayScannerSuccess() {
    std::cout << "Ship is found!" << std::endl;
}

void ConsoleDisplayer::displayScannerFailure() {
    std::cout << "Ship is not found!" << std::endl;
}

void ConsoleDisplayer::displayIncorrectChoiсeInput() {
    std::cout << "Wrong choice, try again!" << std::endl;
}

void ConsoleDisplayer::displayAddingAbility() {
    std::cout << "You have got a new ability!" << std::endl;
}

void ConsoleDisplayer::displayException(std::exception& exception) {
    Colors colors;
    std::cerr << colors.red << "Exception caught: " << exception.what() << colors.reset << std::endl;
}

void ConsoleDisplayer::displayGameStart() {
    std::cout << "Start Game - 1\nSave Game - 2\nLoad Game - 3\nQuit Game - 4" << std::endl;
}

void ConsoleDisplayer::displayBotWins() {
    Colors colors;
    std::cout << colors.red << "Game Over" << colors.reset << std::endl;
}

void ConsoleDisplayer::displayPlayerWins() {
    Colors colors;
    std::cout << colors.yellow << "You have won! Congradulations!" << colors.reset << std::endl;
}

void ConsoleDisplayer::displaySavingGame() {
    std::cout << "Saving game..." << std::endl;
}

void ConsoleDisplayer::displayLoadingGame() {
    std::cout << "Loading game..." << std::endl;
}

void ConsoleDisplayer::displayContinueGame() {
    std::cout << "Do you want to continue the game? Y/n" << std::endl;
}

void ConsoleDisplayer::displayNewGame() {
    std::cout << "Do you want to start a new game? y/n" << std::endl;
}
