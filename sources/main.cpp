#include "../include/Game.hpp"

int main() {
    // * Initialize Player And Bot
    Field field = Field(10, 10);
    ShipManager shipManager = ShipManager();
    AbilityManager abilityManager = AbilityManager();

    Field botField = Field(10, 10);
    ShipManager botShipManager = ShipManager();

    Player player = Player(field, shipManager, abilityManager);
    Bot bot = Bot(botField, botShipManager);

    player.setEnemy(&bot);
    bot.setEnemy(&player);

    shipManager.getShip(0)->changeOrientaion(true);
    shipManager.getShip(1)->changeOrientaion(true);

    field.placeShip(shipManager.getShip(0), true, {7, 0});
    field.placeShip(shipManager.getShip(1), true, {0, 7});
    field.placeShip(shipManager.getShip(2), false, {3, 1});
    field.placeShip(shipManager.getShip(3), false, {3, 4});
    field.placeShip(shipManager.getShip(4), false, {2, 6});
    field.placeShip(shipManager.getShip(5), false, {7, 6});
    field.placeShip(shipManager.getShip(6), false, {8, 9});
    field.placeShip(shipManager.getShip(7), false, {4, 8});
    field.placeShip(shipManager.getShip(8), false, {1, 3});
    field.placeShip(shipManager.getShip(9), false, {0, 0});

    botShipManager.getShip(0)->changeOrientaion(true);
    botShipManager.getShip(1)->changeOrientaion(true);

    botField.placeShip(botShipManager.getShip(0), true, {7, 0});
    botField.placeShip(botShipManager.getShip(1), true, {0, 7});
    botField.placeShip(botShipManager.getShip(2), false, {3, 1});
    botField.placeShip(botShipManager.getShip(3), false, {3, 4});
    botField.placeShip(botShipManager.getShip(4), false, {2, 6});
    botField.placeShip(botShipManager.getShip(5), false, {7, 6});
    botField.placeShip(botShipManager.getShip(6), false, {8, 9});
    botField.placeShip(botShipManager.getShip(7), false, {4, 8});
    botField.placeShip(botShipManager.getShip(8), false, {1, 3});
    botField.placeShip(botShipManager.getShip(9), false, {0, 0});

    Game game = Game(player, bot);
    game.startGame();

    return 0;
}
