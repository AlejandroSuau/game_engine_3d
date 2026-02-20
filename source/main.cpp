#include "Game.hpp"
#include <eng.hpp>

#include <memory>

int main() {
    Game* game = new Game();
    eng::Engine& engine = eng::Engine::GetInstance();
    engine.SetApplication(game);

    if (engine.Init(800, 600)) {
        engine.Run();
    }

    engine.Destroy();
    return 0;
}
