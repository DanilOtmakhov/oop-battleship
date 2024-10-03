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

ShipStatus Ship::getStatus() {
    return status;
}

void Ship::setStatus(ShipStatus newStatus) {
    status = newStatus;
}

void Ship::setSegmentCoordinate(int index, Coordinate coordinate) {
    if (index >= length) {
        throw std::out_of_range("Invalid segment index!");
    }
    segments[index].coordinate = coordinate;
}

void Ship::handleTakenDamage(Coordinate coordinate) {
    for (int i = 0; i < length; i++) {
        ShipSegment& currentSegment = segments[i];
        if (currentSegment.coordinate == coordinate) {
            currentSegment.health--;
            if (currentSegment.health == 0) {
                currentSegment.status = SegmentStatus::Destroyed;
                remainingSegments--;
            } else {
                currentSegment.status = SegmentStatus::Damaged;
                status = ShipStatus::Damaged;
            }
        }
        if (remainingSegments == 0) {
            status = ShipStatus::Destroyed;
        }
    }
}
