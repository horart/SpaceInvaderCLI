#include <chrono>

#include "game.h"
#include "gameobject.h"

void Game::update() {
    auto startTime = std::chrono::high_resolution_clock::now();
    beforeUpdate();
    for (auto& [id, obj] : objectsById) {
        obj->update();
    }
    while(!toDestroy.empty()) {
        int id = toDestroy.front();
        objectsById.erase(id);
        toDestroy.pop();
        toDestroySet.erase(id);
    }
    afterUpdate();
    while(std::chrono::high_resolution_clock::now() < startTime + frameDuration);
    renderer->clear();
    for(auto& [id, obj] : objectsById) {
        if(toDestroySet.find(id) != toDestroySet.end()) {
            continue;
        }
        renderer->render(*obj);
    }
    renderer->flush();
}

void Game::removeObject(int id) {
    toDestroy.push(id);
    toDestroySet.insert(id);
}

Game::~Game() {
    for(auto& [id, obj] : objectsById) {
        obj->destroy();
    }
}