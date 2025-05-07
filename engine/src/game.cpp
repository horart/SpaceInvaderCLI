#include "game.h"
#include "gameobject.h"

void Game::update() {
    beforeUpdate();
    while(!toDestroy.empty()) {
        int id = toDestroy.front();
        objectsById.erase(id);
        toDestroy.pop();
    }
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
    toDestroy.push(id);
}

Game::~Game() {
    for(auto& [id, obj] : objectsById) {
        obj->destroy();
    }
}