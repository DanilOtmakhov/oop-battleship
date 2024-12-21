#include "../include/Deserialization.hpp"

Deserialization::Deserialization(nlohmann::json& j) : j(j) {}

void Deserialization::from_json(Field& field, std::string key) {
    if (!j.contains(key)) {
        throw SaveFileHashMismatchException();
    }

    auto& fieldJSON = j[key];

    if (!fieldJSON.contains("columns") || !fieldJSON.contains("rows") || !fieldJSON.contains("field")) {
        throw SaveFileHashMismatchException();
    }

    int columns = fieldJSON["columns"].get<int>();
    int rows = fieldJSON["rows"].get<int>();

    auto& fieldArray = fieldJSON["field"];
    if (!fieldArray.is_array()) {
        throw SaveFileHashMismatchException();
    }

    if (fieldArray.size() != columns * rows) {
        throw SaveFileHashMismatchException();
    }

    for (size_t i = 0; i < fieldArray.size(); ++i) {
        auto& cellData = fieldArray[i];

        int x = cellData["x"].get<int>();
        int y = cellData["y"].get<int>();
        std::string statusStr = cellData["status"].get<std::string>();
        char valueChar = cellData["value"].get<std::string>()[0];

        CellStatus status;
        if (statusStr == "Hidden") {
            status = CellStatus::Hidden;
        } else if (statusStr == "Revealed") {
            status = CellStatus::Revealed;
        } else {
            throw SaveFileHashMismatchException();
        }

        CellValue value = static_cast<CellValue>(valueChar);

        Coordinate coordinate{x, y};
        FieldCell cell;
        cell.coordinate = coordinate;
        cell.status = status;
        cell.value = value;

        if (x < 0 || y < 0 || x >= columns || y >= rows) {
            throw SaveFileHashMismatchException();
        }

        field.setCellStatus(coordinate, status);
        field.setCellValue(coordinate, value);
    }
}

void Deserialization::from_json(ShipManager& manager, std::string key) {
    if (j.contains(key) && j[key].is_array()) {
        for (const auto& shipJson : j[key]) {
            int length = shipJson["length"];
            bool isVertical = shipJson["isVertical"];
            int remainingSegments = shipJson["remainingSegments"];

            ShipStatus shipStatus;
            if (remainingSegments == length) {
                shipStatus = ShipStatus::Untouched;
            } else if (remainingSegments > 0 && remainingSegments < length) {
                shipStatus = ShipStatus::Damaged;
            } else {
                shipStatus = ShipStatus::Destroyed;
            }

            Ship* ship = new Ship(length, isVertical);
            ship->setStatus(shipStatus);
            ship->setRemainingSegments(remainingSegments);

            int index = 0;
            if (shipJson.contains("segments") && shipJson["segments"].is_array()) {
                for (const auto& segmentJson : shipJson["segments"]) {
                    int x = segmentJson["x"];
                    int y = segmentJson["y"];
                    int health = segmentJson["health"];

                    SegmentStatus segmentStatus;
                    if (health == 2) {
                        segmentStatus = SegmentStatus::Untouched;
                    } else if (health == 1) {
                        segmentStatus = SegmentStatus::Damaged;
                    } else {
                        segmentStatus = SegmentStatus::Destroyed;
                    }

                    ship->setSegment(index, {{x, y}, segmentStatus, health});
                    index++;
                }
            }
        }
    } else {
        throw SaveFileHashMismatchException();
    }
}

void Deserialization::from_json(AbilityManager& manager, std::string key) {
    while (!manager.isAbilitiesEmpty()) {
        manager.getAbility();
    }

    if (j.contains(key) && j[key].is_array()) {
        for (const auto& item : j[key]) {
            if (item.is_string()) {
                std::string abilityType = item.get<std::string>();
                if (abilityType == "DoubleDamage") {
                    manager.addAbility(AbilityType::DoubleDamage);
                } else if (abilityType == "Scanner") {
                    manager.addAbility(AbilityType::Scanner);
                } else if (abilityType == "RandomHit") {
                    manager.addAbility(AbilityType::RandomHit);
                } else {
                    throw std::invalid_argument("Invalid ability type.");
                }
            }
        }
    } else {
        throw std::invalid_argument("Invalid JSON structure for ability manager.");
    }
}

void Deserialization::from_json(std::map<char, Command>& newCommands) {
    const auto& jc = j.at("settings");
    std::vector<int> values;

    for (const auto& pair : jc.items()) {
        std::string key = pair.key();
        if (key.size() != 1) {
            throw std::invalid_argument("Invalid key.");
        }

        int value = pair.value();
        if (value < 0 || value > 6) {
            throw std::invalid_argument("Incorrect number of commands.");
        }
        values.push_back(value);
        newCommands[key[0]] = static_cast<Command>(value);
    }

    for (size_t i = 0; i < values.size(); i++) {
        for (size_t j = i + 1; j < values.size(); j++) {
            if (values[i] == values[j]) {
                throw std::invalid_argument("Duplicates in command.");
            }
        }
    }

    if (values.size() != 7) {
        throw std::invalid_argument("Incorrect number of commands.");
    }
}
