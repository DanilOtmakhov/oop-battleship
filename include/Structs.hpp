#ifndef STRUCT_HPP
#define STRUCT_HPP


class Ship;



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





#endif
