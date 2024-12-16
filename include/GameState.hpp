#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "Serialization.hpp"
#include "Deserialization.hpp"
#include "FileWrapper.hpp"
#include "ConsoleDisplayer.hpp"
#include "SaveFileHashMismatchException.hpp"
#include <fstream>
#include <sstream>

class GameState {
    private:
        Player& player;
        Bot& bot;
    public:
        GameState(Player& player, Bot& bot);
        Player& getPlayer();
        Bot& getBot();
        void saveGame(const std::string& file);
        void loadGame(const std::string& file);
        std::string calculateHash(const std::string& data);
};

#endif
