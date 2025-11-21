#include "Game.hpp"

#include <iostream>

bool Game::Init() {
    return true;
}

void Game::Update(float deltaTime) {
    std::cout << "Current deltaTime: " << deltaTime << " seconds." << std::endl;
}

void Game::Destroy() {

}
