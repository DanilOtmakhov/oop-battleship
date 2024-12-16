#ifndef SHIP_HPP
#define SHIP_HPP

#include <iostream>
#include <iomanip>
#include <vector>
#include "Structs.hpp"

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

struct ShipSegment {
    Coordinate coordinate;
    SegmentStatus status = SegmentStatus::Untouched;
    int health = 2;
};

class Ship {
    private:
        int length;
        bool isVertical = false;
        int remainingSegments;
        ShipStatus status = ShipStatus::Untouched;
        std::vector<ShipSegment> segments;
    public:
        Ship(int length, bool isVertical = false);
        int getLength();
        bool getIsVertical();
        void changeOrientaion(bool toVertical = true);
        ShipStatus getStatus();
        void setStatus(ShipStatus newStatus);
        void setSegmentCoordinate(int index, Coordinate coordinate);
        SegmentStatus getSegmentStatusByIndex(int index);
        Coordinate getSegmentCoordinateByIndex(int index);
        int getSegmentIndexByCoordinate(Coordinate coordinate);
        void handleTakenDamage(int segmentIndex, int damage = 1);
        int getRemainingSegments();
        void setRemainingSegments(int numberOfSegments);
        std::vector<ShipSegment> getSegments();
        void setSegment(int index, ShipSegment segment);
        Coordinate getCoordinate();
};

#endif
