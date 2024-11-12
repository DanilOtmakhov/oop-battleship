#ifndef STRUCT_HPP
#define STRUCT_HPP


class Ship;

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

enum class SegmentStatus {
    Untouched,
    Damaged,
    Destroyed
};

enum class ShipStatus {
    Untouched,
    Damaged,
    Destroyed
};

enum class AttackResult {
    ShipDestroyed,
    Missed,
    ShipDamaged,
    AlreadyAttacked
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
