#include "game.h"
#include "gameobject.h"

void Game::update() {
    beforeUpdate();
    for (auto& [id, obj] : objectsById) {
        obj->update();
    }
    afterUpdate();
}

void Game::removeObject(int id) {
    objectsById.erase(id);
}

Game::~Game() {
    for(auto& [id, obj] : objectsById) {
        obj->destroy();
    }
}