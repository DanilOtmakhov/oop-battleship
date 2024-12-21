#include "../include/GameController.hpp"
#include "../include/Setup.hpp"

int main() {
    // Initialize Player And Bot
    Field field = Field(10, 10);
    ShipManager shipManager = ShipManager();
    AbilityManager abilityManager = AbilityManager();

    Field botField = Field(10, 10);
    ShipManager botShipManager = ShipManager();

    Player player = Player(field, shipManager, abilityManager);
    Bot bot = Bot(botField, botShipManager);

    player.setEnemy(&bot);
    bot.setEnemy(&player);

    ConsoleDisplayer displayer = ConsoleDisplayer();

    try {
        for (size_t i = 0; i < shipManager.getShips().size(); i++) {
            field.placeShipRandomly(shipManager.getShips()[i]);
            botField.placeShipRandomly(botShipManager.getShips()[i]);
        }
    }
    catch (UnableToPlaceShipsException& e) {
        displayer.displayException(e);
        return 0;
    }

    GameState gameState = GameState(player, bot);
    Game game = Game(player, bot, gameState, displayer);

    InputHandler inputHandler = InputHandler();
    Setup setup = Setup(inputHandler);
    try {
        setup.deserializeSetup();
    } catch (std::exception& e) {
        displayer.displayException(e);
    }

    OutputObserver<ConsoleDisplayer>* outputObserver = new OutputObserver<ConsoleDisplayer>(displayer, gameState);
    game.addObserver(outputObserver);

    GameController<InputHandler, ConsoleDisplayer> controller = GameController<InputHandler, ConsoleDisplayer>(game, inputHandler, displayer);
    controller.initializeGame();

    return 0;
}
