#ifndef FIELD_HPP
#define FIELD_HPP

#include <iostream>
#include <vector>
#include "Ship.hpp"
#include "Structs.hpp"
#include "OutOfBoundsException.hpp"
#include "IncorrectShipPlacementException.hpp"
#include "AlreadyAttackedCellException.hpp"


class Field {
    private:
        int rows;
        int columns;
        std::vector <std::vector <FieldCell>> field;
        bool checkPlaceForShip(int ShipLength, bool isVertical, Coordinate coordinate);
    public:
        Field(int rows, int columns);
        Field(const Field& other);
        Field& operator = (const Field& other);
        Field(Field&& other);
        Field& operator = (Field&& other);
        bool isCoordinateCorrect(Coordinate coordinate);
        int getRows();
        int getColumns();
        void setCellStatus(Coordinate coordinate, CellStatus status);
        CellStatus getCellStatus(Coordinate coordinate);
        void setCellValue(Coordinate coordinate, CellValue value);
        CellValue getCellValue(Coordinate coordinate);
        void placeShip(Ship* ship, bool isVertical, Coordinate coordinate);
        AttackResult handleAttack(Coordinate coordinate, int damage = 1);
        AttackResult handleRandomAttack();
        bool isShipInCell(Coordinate coordinate);
};

#endif
