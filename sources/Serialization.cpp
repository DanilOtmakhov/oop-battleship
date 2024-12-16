#include "../include/Serialization.hpp"

Serialization::Serialization(nlohmann::json& j) : j(j) {}

void Serialization::to_json(Field& field, std::string key) {
    nlohmann::json jsonField = nlohmann::json {
        {"rows", field.getRows()},
        {"columns", field.getColumns()},
        {"field", nlohmann::json::array()}
    };

    std::vector <std::vector <FieldCell>> fieldCells = field.getField();
    for (int i = 0; i < field.getRows(); i++) {
        for (int j = 0; j < field.getColumns(); j++) {

            std::string statusString;
            if (fieldCells[i][j].status == CellStatus::Hidden) {
                statusString = "Hidden";
            } else {
                statusString = "Revealed";
            }

            std::string valueString;
            switch (fieldCells[i][j].value) {
                case CellValue::Hidden:
                    valueString = " ";
                    break;
                case CellValue::Revealed:
                    valueString = "*";
                    break;
                case CellValue::ShipPart:
                    valueString = "S";
                    break;
                case CellValue::Damaged:
                    valueString = "x";
                    break;
                case CellValue::Destroyed:
                    valueString = "0";
                    break;
                case CellValue::ShipDestroyed:
                    valueString = "D";
                    break;
                default:
                    valueString = " ";
                    break;
            }

            jsonField["field"].push_back({
                {"x", j/*fieldCells[i][j].coordinate.x*/},
                {"y", i/*fieldCells[i][j].coordinate.y*/},
                {"status", statusString},
                {"value", valueString}
            });
        }
    }

    j[key] = jsonField;
}

void Serialization::to_json(ShipManager& manager, std::string key) {
    j[key] = nlohmann::json::array();

    std::vector <Ship*> ships = manager.getShips();
    for (int i = 0; i < ships.size(); i++) {
        nlohmann::json shipJson = {
            {"length", ships[i]->getLength()},
            {"isVertical", ships[i]->getIsVertical()},
            {"remainingSegments", ships[i]->getRemainingSegments()},
            {"segments", nlohmann::json::array()}
        };

        std::vector <ShipSegment> segments = ships[i]->getSegments();
        for (int j = 0; j < segments.size(); j++) {
            shipJson["segments"].push_back({
                {"x", segments[j].coordinate.x},
                {"y", segments[j].coordinate.y},
                {"health", segments[j].health}
            });
        }
        j[key].push_back(shipJson);
    }
}

void Serialization::to_json(AbilityManager& manager, std::string key) {
    j[key] = nlohmann::json::array();

    std::vector <AbilityType> types = manager.getAbilitiesTypes();
    for (const auto& type : types) {
        std::string typeString;
        if (type == AbilityType::DoubleDamage) {
            typeString = "DoubleDamage";
        } else if (type == AbilityType::Scanner) {
            typeString = "Scanner";
        } else {
            typeString = "RandomHit";
        }
        j[key].push_back(typeString);
    }
}
