#include "game.h"
#include "gameobject.h"

void Game::update() {
    beforeUpdate();
    for (auto& [id, obj] : objectsById) {
        obj->update();
    }
    afterUpdate();
    renderer->clear();
    for(auto& [id, obj] : objectsById) {
        renderer->render(*obj);
    }
    renderer->flush();
}

void Game::removeObject(int id) {
    objectsById.erase(id);
}

Game::~Game() {
    for(auto& [id, obj] : objectsById) {
        obj->destroy();
    }
}