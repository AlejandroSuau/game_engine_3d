#include "Game.hpp"
#include <eng.hpp>

int main() {
    Game* game = new Game();
    eng::Engine& engine = eng::Engine::GetInstance();
    engine.SetApplication(game);

    if (engine.Init(800, 600)) {
        engine.Run();
    }

    engine.Destroy();

    delete game;

    return 0;
}
