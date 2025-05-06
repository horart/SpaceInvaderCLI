#include <memory>

#include "game.h"

template <typename T, typename ...Args>
std::shared_ptr<T> Game::createObject(Args&&... args) {
    std::shared_ptr<T> obj = std::make_shared<T>(shared_from_this(), ++lastId, std::forward<Args>(args)...);
    obj->init();
    objectsById.emplace(lastId, obj);
    return obj;
}