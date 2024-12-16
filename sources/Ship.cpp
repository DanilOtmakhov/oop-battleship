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

int Ship::getRemainingSegments() {
    return remainingSegments;
}

void Ship::setRemainingSegments(int numberOfSegments) {
    remainingSegments = numberOfSegments;
}

std::vector<ShipSegment> Ship::getSegments() {
    return segments;
}

void Ship::setSegment(int index, ShipSegment segment) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Invalid segment index!");
    }
    segments[index] = segment;
}

Coordinate Ship::getCoordinate() {
    return segments[0].coordinate;
}
