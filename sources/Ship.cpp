#include "../include/Ship.hpp"


Ship::Ship(int length, bool isVertical)
    : length(length), isVertical(isVertical), remainingSegments(length), segments(length) {
    if (length < 1 || length > 4) {
        throw std::invalid_argument("Length of ship must be between 1 and 4");
    }
}

int Ship::getLength() {
    return length;
}

bool Ship::getIsVertical(){
    return isVertical;
}

void Ship::changeOrientaion(bool toVertical) {
    isVertical = toVertical;
}

ShipStatus Ship::getStatus() {
    return status;
}

void Ship::setStatus(ShipStatus newStatus) {
    status = newStatus;
}

void Ship::setSegmentCoordinate(int index, Coordinate coordinate) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Invalid segment index!");
    }
    segments[index].coordinate = coordinate;
}

int Ship::getSegmentIndexByCoordinate(Coordinate coordinate) {
    for (int i = 0; i < length; i++) {
        ShipSegment& currentSegment = segments[i];
        if (currentSegment.coordinate == coordinate) {
            return i;
        }
    }
}

SegmentStatus Ship::getSegmentStatusByIndex(int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Invalid segment index!");
    }
    return segments[index].status;
}

Coordinate Ship::getSegmentCoordinateByIndex(int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Invalid segment index!");
    }
    return segments[index].coordinate;
}

void Ship::handleTakenDamage(int segmentIndex, int damage) {
    ShipSegment& currentSegment = segments[segmentIndex];
    currentSegment.health -= damage;
    if (currentSegment.health <= 0) {
        currentSegment.status = SegmentStatus::Destroyed;
        remainingSegments--;
    } else {
        currentSegment.status = SegmentStatus::Damaged;
        status = ShipStatus::Damaged;
    }
    if (remainingSegments == 0) {
        status = ShipStatus::Destroyed;
    }
}

Coordinate Ship::getCoordinate() {
    return segments[0].coordinate;
}

void Ship::to_json(nlohmann::json& j, const Ship& s) {
    j = nlohmann::json{
        {"length", s.length},
        {"isVertical", s.isVertical},
        {"remainingSegments", s.remainingSegments},
        {"status", s.status},
        {"segments", s.segments}
    };
}

void Ship::from_json(const nlohmann::json& j, Ship& s) {
    j.at("length").get_to(s.length);
    j.at("isVertical").get_to(s.isVertical);
    j.at("remainingSegments").get_to(s.remainingSegments);
    j.at("status").get_to(s.status);
    j.at("segments").get_to(s.segments);
}
