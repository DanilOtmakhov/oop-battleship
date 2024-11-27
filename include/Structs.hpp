#ifndef STRUCT_HPP
#define STRUCT_HPP

#include <nlohmann/json.hpp>
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

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Coordinate, x, y)
};

struct FieldCell {
    Coordinate coordinate;
    CellStatus status;
    CellValue value;
    Ship* ship = nullptr;

    friend void to_json(nlohmann::json& j, const FieldCell& cell) {
        j = nlohmann::json{
            {"coordinate", cell.coordinate},
            {"status", cell.status},
            {"value", cell.value}
        };

        if (cell.ship) {
            j["ship"] = *cell.ship;
        }
    }

    friend void from_json(const nlohmann::json& j, FieldCell& cell) {
        j.at("coordinate").get_to(cell.coordinate);
        j.at("status").get_to(cell.status);
        j.at("value").get_to(cell.value);

        if (j.contains("ship")) {
            cell.ship = new Ship;
            j.at("ship").get_to(*cell.ship);
        }
    }
};

struct ShipSegment {
    Coordinate coordinate;
    SegmentStatus status = SegmentStatus::Untouched;
    int health = 2;

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ShipSegment, coordinate, status, health)
};

#endif
