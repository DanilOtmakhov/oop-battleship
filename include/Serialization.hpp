#ifndef SERIALIZATION_HPP
#define SERIALIZATION_HPP

#include <nlohmann/json.hpp>
#include "Field.hpp"
#include "ShipManager.hpp"
#include "AbilityManager.hpp"
#include "Player.hpp"
#include "Bot.hpp"

class Serialization {
    private:
        nlohmann::json& j;
    public:
        Serialization(nlohmann::json& j);
        void to_json(Field& field, std::string key);
        void to_json(ShipManager& manager, std::string key);
        void to_json(AbilityManager& manager, std::string key);
};

#endif
