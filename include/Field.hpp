#ifndef FIELD_HPP
#define FIELD_HPP

#include <iostream>
#include <vector>
#include <random>
#include "Ship.hpp"
#include "Structs.hpp"
#include "OutOfBoundsException.hpp"
#include "IncorrectShipPlacementException.hpp"
#include "UnableToPlaceShipsException.hpp"
#include "AlreadyAttackedCellException.hpp"

enum class CellStatus {
    Hidden,
    Revealed
};

enum class CellValue : char {
    Hidden = ' ',
    Revealed = '*',
    ShipPart = 'S',
    Damaged = 'x',
    Destroyed = '0',
    ShipDestroyed = 'D'
};

struct FieldCell {
    Coordinate coordinate;
    CellStatus status;
    CellValue value;
    Ship* ship = nullptr;
};

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
        std::vector <std::vector <FieldCell>> getField();
        void setCellStatus(Coordinate coordinate, CellStatus status);
        CellStatus getCellStatus(Coordinate coordinate);
        void setCellValue(Coordinate coordinate, CellValue value);
        CellValue getCellValue(Coordinate coordinate);
        void placeShip(Ship* ship, bool isVertical, Coordinate coordinate);
        AttackResult handleAttack(Coordinate coordinate, int damage = 1);
        AttackResult handleRandomAttack();
        bool isShipInCell(Coordinate coordinate);
        void placeShipRandomly(Ship* ship);
        //void revealCells();
};

#endif
