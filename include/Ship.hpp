#ifndef SHIP_HPP
#define SHIP_HPP

#include <iostream>
#include <iomanip>
#include <vector>
#include "Structs.hpp"
#include <nlohmann/json.hpp>


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
        Coordinate getCoordinate();
        friend void to_json(nlohmann::json& j, const Ship& s);
        friend void from_json(const nlohmann::json& j, Ship& s);
};

#endif
