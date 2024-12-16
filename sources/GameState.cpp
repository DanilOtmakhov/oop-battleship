#include "../include/GameState.hpp"

GameState::GameState(Player& player, Bot& bot) : player(player), bot(bot) {}

std::string GameState::calculateHash(const std::string& data) {
    std::hash<std::string> hash_fn;
    size_t hash = hash_fn(data);

    std::stringstream ss;
    ss << std::hex << hash;
    return ss.str();
}

Player& GameState::getPlayer() {
    return player;
}

Bot& GameState::getBot() {
    return bot;
}

FileWrapper& operator<<(FileWrapper& wrapper, GameState& state) {
    nlohmann::json j;
    nlohmann::json data;
    Serialization serialization(data);

    Player& player = state.getPlayer();
    Bot& bot = state.getBot();

    serialization.to_json(player.getField(), "playerField");
    serialization.to_json(player.getShipManager(), "playerShipManager");
    serialization.to_json(player.getAbilityManager(), "playerAbilityManager");
    serialization.to_json(bot.getField(), "botField");
    serialization.to_json(bot.getShipManager(), "botShipManager");

    std::string jsonStr = data.dump();

    std::string hash = state.calculateHash(jsonStr);

    j["data"] = data;
    j["hash"] = hash;

    try {
        wrapper.write(j);
    } catch (UnableToOpenFileException& exception) {
        ConsoleDisplayer displayer;
        displayer.displayException(exception);
    }

    return wrapper;
}

FileWrapper& operator>>(FileWrapper& wrapper, GameState& state) {
    nlohmann::json j;

    try {
        wrapper.read(j);
    }
    catch (UnableToOpenFileException& exception) {
        ConsoleDisplayer displayer;
        displayer.displayException(exception);
        return wrapper;
    }

    nlohmann::json data = j.at("data");
    std::string savedHash = j.at("hash").get<std::string>();

    std::string jsonStr = data.dump();
    std::string calculatedHash = state.calculateHash(jsonStr);
    if (calculatedHash != savedHash) {
        throw SaveFileHashMismatchException();
    }

    Player& player = state.getPlayer();
    Bot& bot = state.getBot();

    Deserialization deserialization(data);
    deserialization.from_json(player.getShipManager(), "playerShipManager");
    deserialization.from_json(player.getField(), "playerField");
    deserialization.from_json(player.getAbilityManager(), "playerAbilityManager");
    deserialization.from_json(bot.getShipManager(), "botShipManager");
    deserialization.from_json(bot.getField(), "botField");

    for (auto* ship: player.getShipManager().getShips()) {
        std::vector <ShipSegment> segments = ship->getSegments();
        for (auto& segment : segments) {
            player.getField().getField()[segment.coordinate.y][segment.coordinate.y].ship = ship;
        }
    }

    return wrapper;
}

void GameState::saveGame(const std::string& file) {
    std::ofstream ofs(file, std::ofstream::out | std::ofstream::trunc);
    FileWrapper wrapper(file);
    wrapper << *this;
}

void GameState::loadGame(const std::string& file) {
    FileWrapper wrapper(file);
    wrapper >> *this;
}
