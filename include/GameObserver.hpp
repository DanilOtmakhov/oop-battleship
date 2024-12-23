#ifndef GAME_OBSERVER_HPP
#define GAME_OBSERVER_HPP

#include "Game.hpp"

class GameObserver {
    public:
        virtual void abilityUsed() = 0;
        virtual void roundCompleted() = 0;
        virtual void playerWin() = 0;
        virtual void botWin() = 0;
        virtual void saveSuccess() = 0;
        virtual ~GameObserver() {};
};

template <class Output>
class OutputObserver : public GameObserver {
    private:
        Output& output;
        GameState& gameState;
    public:
        OutputObserver(Output& output, GameState& gameState) : output(output), gameState(gameState) {};

        void abilityUsed() override {
            output.displayAbilityUsed();
        }

        void roundCompleted() override {
            output.displayFields(gameState.getPlayer().getField(), gameState.getBot().getField());
            output.displayRoundCompleted();
        }

        void playerWin() override {
            output.displayPlayerWins();
        }

        void botWin() override {
            output.displayBotWins();
        }

        void saveSuccess() override {
            output.displaySaveFinished();
        }
};

#endif
