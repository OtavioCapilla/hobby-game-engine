#include <engine/core/Game.h>
#include <filesystem>

int main(){
    GameConfig config;

    auto root = std::filesystem::current_path();
    config.assetRoot =
        (root / "games/demo/assets/").string();

    Game game(config);
    game.run();
    return 0;
}