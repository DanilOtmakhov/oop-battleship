#ifndef DESERIALIZATION_HPP
#define DESERIALIZATION_HPP

#include <nlohmann/json.hpp>
#include "Field.hpp"
#include "ShipManager.hpp"
#include "AbilityManager.hpp"
#include "Player.hpp"
#include "Bot.hpp"
#include "SaveFileHashMismatchException.hpp"

class Deserialization {
    private:
        nlohmann::json& j;
    public:
        Deserialization(nlohmann::json& j);
        void from_json(Field& field, std::string key);
        void from_json(ShipManager& manager, std::string key);
        void from_json(AbilityManager& manager, std::string key);
};

#endif
