#pragma once

#include <memory>
#include <unordered_map>
#include <utility>
#include <queue>
#include <chrono>
#include <set>

#include "renderer.h"

class GameObject;

class Game : public std::enable_shared_from_this<Game> {
private:
    int lastId = 0;
    std::unique_ptr<Renderer> renderer;
    std::queue<int> toDestroy;
    std::set<int> toDestroySet;
    Point gameSize;
protected:
    std::unordered_map<int, std::shared_ptr<GameObject>> objectsById;
    std::chrono::duration<int, std::milli> frameDuration = std::chrono::milliseconds(1000 / 20);
private:
    virtual void beforeUpdate() {}
    virtual void afterUpdate() {}
public:
    Game(std::unique_ptr<Renderer> r, 
    std::chrono::duration<int, std::milli> frameDuration = std::chrono::milliseconds(1000 / 20)) :
        renderer(std::move(r)), gameSize(renderer->getGameSize()), frameDuration(frameDuration) {}
    virtual void setFrameDuration(std::chrono::duration<int, std::milli> frameDuration = std::chrono::milliseconds(1000 / 20)) {
        this->frameDuration = frameDuration;
    }
    Point getGameSize() const {
        return gameSize;
    }
    template <typename T, typename ...Args>
    std::shared_ptr<T> createObject(Args&&... args);
    virtual void init() {}
    void update();
    void removeObject(int id);
    virtual ~Game();
};

#include "game.tpp"