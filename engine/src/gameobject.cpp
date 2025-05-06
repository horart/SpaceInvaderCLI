#include "gameobject.h"
#include "game.h"

GameObject::GameObject(std::weak_ptr<Game> g, int id, Point p)
    : game(g), pos(p), posToBeSet(p), id(id) {
}

Point GameObject::getPosition() const {
    return pos;
}

std::shared_ptr<std::vector<std::shared_ptr<RenderingPrimitive>>> GameObject::getPrimitives() const {
    return {};
}

void GameObject::setPosition(Point newPos) {
    posToBeSet = newPos;
}

void GameObject::update() {
    beforeUpdate();
    if (pos != posToBeSet) {
        pos = posToBeSet;
    }
}

void GameObject::destroy() {
    onDestroy();
    if (std::shared_ptr<Game> g = game.lock()) {
        g->removeObject(id);
    }
}
