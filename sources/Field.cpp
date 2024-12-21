#include "../include/Field.hpp"


Field::Field(int rows, int columns) : rows(rows), columns(columns) {
    for (int i = 0; i < rows; i++) {
        std::vector<FieldCell> row;
        for (int j = 0; j < columns; j++) {
            row.push_back(FieldCell{{i, j}, CellStatus::Hidden, CellValue::Hidden});
        }
        field.push_back(row);
    }
}

Field::Field(const Field& other) : rows(other.rows), columns(other.columns), field(other.field) {}

Field& Field::operator = (const Field& other) {
    if (this != &other) {
        rows = other.rows;
        columns = other.columns;
        field = other.field;
    }
    return *this;
}

Field::Field(Field&& other) : rows(other.rows), columns(other.columns), field(std::move(other.field)) {
    other.rows = 0;
    other.columns = 0;
}

Field& Field::operator = (Field&& other) {
    if (this != &other) {
        rows = other.rows;
        columns = other.columns;
        field = std::move(other.field);
        other.rows = 0;
        other.columns = 0;
    }
    return *this;
}

bool Field::isCoordinateCorrect(Coordinate coordinate) {
    return 0 <= coordinate.x && coordinate.x < columns && 0 <= coordinate.y && coordinate.y < rows;
}

bool Field::checkPlaceForShip(int shipLength, bool isVertical, Coordinate coordinate) {
    int x0 = coordinate.x;
    int y0 = coordinate.y;
    int x1 = isVertical ? x0 : x0 + shipLength - 1;
    int y1 = isVertical ? y0 + shipLength - 1 : y0;

    if (!isCoordinateCorrect({x0, y0})) {
        return false;
    }

    if (!isCoordinateCorrect({x1, y1})) {
        return false;
    }

    for (int i = 0; i < shipLength; i++) {
        int x = isVertical ? x0 : x0 + i;
        int y = isVertical ? y0 + i : y0;

        if (field[y][x].ship) return false;

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;
                int neighborX = x + dx;
                int neighborY = y + dy;

                if (neighborX >= 0 && neighborX < columns && neighborY >= 0 && neighborY < rows) {
                    if (field[neighborY][neighborX].ship) return false;
                }
            }
        }
    }

    return true;
}

int Field::getRows() {
    return rows;
}

int Field::getColumns() {
    return columns;
}

std::vector <std::vector <FieldCell>> Field::getField() {
    return field;
}

void Field::setCellStatus(Coordinate coordinate, CellStatus status) {
    if (!isCoordinateCorrect(coordinate)) {
        throw OutOfBoundsException();
    }

    field[coordinate.y][coordinate.x].status = status;
}

CellStatus Field::getCellStatus(Coordinate coordinate) {
    if (!isCoordinateCorrect(coordinate)) {
        throw OutOfBoundsException();
    }

    return field[coordinate.y][coordinate.x].status;
}

void Field::setCellValue(Coordinate coordinate, CellValue value) {
    if (!isCoordinateCorrect(coordinate)) {
        throw OutOfBoundsException();
    }

    field[coordinate.y][coordinate.x].value = value;
}

CellValue Field::getCellValue(Coordinate coordinate) {
    if (!isCoordinateCorrect(coordinate)) {
        throw OutOfBoundsException();
    }

    return field[coordinate.y][coordinate.x].value;
}

void Field::placeShip(Ship* ship, bool isVertical, Coordinate coordinate) {
    if (!checkPlaceForShip(ship->getLength(), isVertical, coordinate)) {
        throw IncorrectShipPlacementException();
    }

    int x0 = coordinate.x;
    int y0 = coordinate.y;
    int length = (*ship).getLength();

    for (int i = 0; i < length; i++) {
        if (isVertical) {
            ship->setSegmentCoordinate(i, {x0, y0 + i});
            setCellValue({x0, y0 + i}, CellValue::ShipPart);
            field[y0 + i][x0].ship = ship;
        } else {
            ship->setSegmentCoordinate(i, {x0 + i, y0});
            setCellValue({x0 + i, y0}, CellValue::ShipPart);
            field[y0][x0 + i].ship = ship;
        }
    }
}

AttackResult Field::handleAttack(Coordinate coordinate, int damage) {
    if (!isCoordinateCorrect(coordinate)) {
        throw OutOfBoundsException();
    }

    FieldCell& cell = field[coordinate.y][coordinate.x];

    switch (cell.value) {
        case CellValue::Hidden:
            cell.value = CellValue::Revealed;
            cell.status = CellStatus::Revealed;
            break;
        case CellValue::ShipPart:
            if (damage == 1) {
                cell.value = CellValue::Damaged;
            } else {
                cell.value = CellValue::Destroyed;
            }
            cell.status = CellStatus::Revealed;
            break;
        case CellValue::Damaged:
            cell.value = CellValue::Destroyed;
            break;
        default:
            throw AlreadyAttackedCellException();
    }

    if (cell.ship) {
        int segmentIndex = cell.ship->getSegmentIndexByCoordinate(coordinate);
        cell.ship->handleTakenDamage(segmentIndex, damage);

        if (cell.ship->getStatus() == ShipStatus::Destroyed) {
            bool isVertical = cell.ship->getIsVertical();
            int shipLength = cell.ship->getLength();
            int x0 = cell.ship->getCoordinate().x;
            int y0 = cell.ship->getCoordinate().y;

            for (int i = 0; i < shipLength; i++) {
                int x = isVertical ? x0 : x0 + i;
                int y = isVertical ? y0 + i : y0;

                field[y][x].value = CellValue::ShipDestroyed;

                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (dx == 0 && dy == 0) continue;
                        int neighborX = x + dx;
                        int neighborY = y + dy;

                        if (isCoordinateCorrect({neighborX, neighborY}) && !field[neighborY][neighborX].ship) {
                            field[neighborY][neighborX].value = CellValue::Revealed;
                        }
                    }
                }
            }
            return AttackResult::ShipDestroyed;
        } else {
            return AttackResult::ShipDamaged;
        }
    }

    return AttackResult::Missed;
}

AttackResult Field::handleRandomAttack() {
    int target_x = rand() % columns;
    int target_y = rand() % rows;

    return handleAttack({target_x, target_y});
}

bool Field::isShipInCell(Coordinate coordinate) {
    if (!isCoordinateCorrect(coordinate)) {
        throw OutOfBoundsException();
    }
    return field[coordinate.y][coordinate.x].ship ? true : false;
}

void Field::placeShipRandomly(Ship* ship) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, columns - 1);
    std::uniform_int_distribution<> disY(0, rows - 1);
    std::uniform_int_distribution<> disOrientation(0, 1);

    int j = 0;
    while (true) {
        int randomX = disX(gen);
        int randomY = disY(gen);
        int randOrientation = disOrientation(gen);

        bool isVertical = (randOrientation == 1);
        ship->changeOrientation(isVertical);

        try {
            placeShip(ship, isVertical, {randomX, randomY});
            return;
        } catch (IncorrectShipPlacementException& exception) {
            j++;
            if (j >= 100) {
                throw UnableToPlaceShipsException();
            }
        }
    }
}
