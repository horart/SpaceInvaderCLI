#pragma once

#include <memory>
#include <unordered_map>
#include <utility>

#include "renderer.h"

class GameObject;

class Game : public std::enable_shared_from_this<Game> {
private:
    int lastId = 0;
protected:
    std::unordered_map<int, std::shared_ptr<GameObject>> objectsById;
private:
    virtual void beforeUpdate() {}
    virtual void afterUpdate() {}
public:
    template <typename T, typename ...Args>
    std::shared_ptr<T> createObject(Args&&... args);
    void update();
    void removeObject(int id);
    virtual ~Game();
};

#include "game.tpp"