#include "../include/Field.hpp"
#include "../include/Ship.hpp"
#include "../include/ShipManager.hpp"


void display(Field field) {
    int rows = field.getRows();
    int columns = field.getColumns();
    Colors colors;
    std::cout << colors.white << "\033[1m" << std::setw((4 * columns + 1) / 2 + 6) << "Battle Ship" << colors.reset << std::endl;
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
    std::cout << colors.red << static_cast<char>(CellValue::Destroyed) << colors.white << " - destroyed ship." << colors.reset << std::endl;
}


int main() {
    Ship ship1 = Ship(4, true);
    Ship ship2 = Ship(2, false);
    Ship ship3 = Ship(3, false);
    Field gamefield = Field(10, 10);
    gamefield.placeShip(&ship1, ship1.getIsVertical(), {9, 6});
    gamefield.placeShip(&ship2, ship2.getIsVertical(), {1, 1});
    gamefield.placeShip(&ship3, ship3.getIsVertical(), {5, 6});

    gamefield.handleAttack({1, 1});
    ship2.handleTakenDamage({1, 1});

    gamefield.handleAttack({1, 1});
    ship2.handleTakenDamage({1, 1});

    gamefield.handleAttack({2, 1});
    ship2.handleTakenDamage({2, 1});

    gamefield.handleAttack({2, 1});
    ship2.handleTakenDamage({2, 1});

    display(gamefield);

    return 0;
}
