#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <nlohmann/json.hpp>
#include <fstream>

class GameState {
    private:
        Game& game;
    public:
        void saveGame();
        void loadGame();
};

#endif
