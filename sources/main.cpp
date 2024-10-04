#include "../include/Field.hpp"
#include "../include/Ship.hpp"
#include "../include/ShipManager.hpp"


void display(Field field) {
    int rows = field.getRows();
    int columns = field.getColumns();
    Colors colors;
    //std::cout << colors.white << "\033[1m" << std::setw((4 * columns + 1) / 2 + 6) << "Battle Ship" << colors.reset << std::endl;
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
                    std::cout << colors.yellow << ' ' << static_cast<char>(value) << ' '; //Для просмотра
                    //std::cout << colors.yellow << ' ' << static_cast<char>(CellValue::Hidden) << ' '; //Для игры
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
    std::cout << colors.white << "Designation of cell status:" << std::endl;
    std::cout << colors.blue << static_cast<char>(CellValue::Revealed) << colors.white << " - missed attack;" << std::endl;
    std::cout << colors.yellow << static_cast<char>(CellValue::ShipPart) << colors.white << " - untouched segment of the ship;" << std::endl;
    std::cout << colors.red << static_cast<char>(CellValue::Damaged) << colors.white << " - damaged segment of the ship;" << std::endl;
    std::cout << colors.red << static_cast<char>(CellValue::Destroyed) << colors.white << " - destroyed ship segment." << colors.reset << std::endl;
}


int main() {
    Field gamefield = Field(10, 10);
    ShipManager manager = ShipManager();

    std::vector<Ship*> ships = manager.getShips();

    ships[0]->changeOrientaion(true);
    ships[1]->changeOrientaion(true);

    gamefield.placeShip(ships[0], true, {7, 0});
    gamefield.placeShip(ships[1], true, {0, 7});
    gamefield.placeShip(ships[2], false, {3, 1});
    gamefield.placeShip(ships[3], false, {3, 4});
    gamefield.placeShip(ships[4], false, {2, 6});
    gamefield.placeShip(ships[5], false, {7, 6});
    gamefield.placeShip(ships[6], false, {8, 9});
    gamefield.placeShip(ships[7], false, {4, 8});
    gamefield.placeShip(ships[8], false, {1, 3});
    gamefield.placeShip(ships[9], false, {0, 0});

    for (int i = 0; i < 100; i++) {
        gamefield.handleRandomAttack();
    }

    display(gamefield);
    /*
    for (int i = 0; i < 10; i++) {
        if (ships[i]->getStatus() == ShipStatus::Untouched) {
            std::cout << "Ship " << i + 1 << ": " << "Untoched" << std::endl;
        } else if (ships[i]->getStatus() == ShipStatus::Damaged) {
            std::cout << "Ship " << i + 1 << ": " << "Damaged" << std::endl;
        } else {
            std::cout << "Ship " << i + 1 << ": " << "Destroyed" << std::endl;
        }
    }
    */

    return 0;
}
