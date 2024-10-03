#ifndef FIELD_HPP
#define FIELD_HPP

#include <iostream>
#include <vector>
#include "Ship.hpp"
#include "Structs.hpp"


class Field {
    private:
        int rows;
        int columns;
        std::vector<std::vector<FieldCell>> field;
        bool isCoordinateCorrect(Coordinate coordinate);
        bool checkPlaceForShip(int ShipLength, bool isVertical, Coordinate coordinate);
    public:
        Field(int rows, int columns);
        Field(const Field& other);
        Field& operator = (const Field& other);
        Field(Field&& other);
        Field& operator = (Field&& other);
        int getRows();
        int getColumns();
        void setCellStatus(Coordinate coordinate, CellStatus status);
        CellStatus getCellStatus(Coordinate coordinate);
        void setCellValue(Coordinate coordinate, CellValue value);
        CellValue getCellValue(Coordinate coordinate);
        void placeShip(Ship* ship, bool isVertical, Coordinate coordinate);
        void handleAttack(Coordinate coordinate);
};

#endif
