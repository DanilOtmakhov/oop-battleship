#ifndef STRUCT_HPP
#define STRUCT_HPP


class Ship;

enum class CellStatus {Hidden, Revealed};

enum class CellValue : char {
    Hidden = ' ',
    Revealed = '*',
    ShipPart = 'S',
    Damaged = 'x',
    Destroyed = '0'
};

enum class SegmentStatus {Untouched, Damaged, Destroyed};

enum class ShipStatus {Untouched, Damaged, Destroyed};

struct Colors {
    const std::string white = "\033[97m";
    const std::string blue = "\033[36m";
    const std::string red = "\033[91m";
    const std::string yellow = "\033[33m";
    const std::string reset = " \033[0m";
};

struct Coordinate {
    int x;
    int y;

    bool operator == (const Coordinate& other) {
        return std::tie(x, y) == std::tie(other.x, other.y);
    }
};

struct FieldCell {
    Coordinate coordinate;
    CellStatus status;
    CellValue value;
    Ship* ship = nullptr;
};

struct ShipSegment {
    Coordinate coordinate;
    SegmentStatus status = SegmentStatus::Untouched;
    int health = 2;
};

#endif
