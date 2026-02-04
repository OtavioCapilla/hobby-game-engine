#include <engine/core/Game.h>
#include <filesystem>
#include "GameSetup.h"

int main()
{
    GameConfig config;

    auto root = std::filesystem::current_path();
    config.assetRoot =
        (root / "games/demo/assets/").string();

    Game game(config);
    EntityID player = GameSetup::setup(game.getScene(), game.getAssets(), config);
    game.setPlayer(player);
    game.run();
    return 0;
}