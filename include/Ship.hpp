#ifndef SHIP_HPP
#define SHIP_HPP

#include <iostream>
#include <iomanip>
#include <vector>
#include "Structs.hpp"


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
        int getSegmentIndexByCoordinate(Coordinate coordinate);
        void handleTakenDamage(int segmentIndex);
};

#endif
