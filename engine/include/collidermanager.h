#pragma once

#include <unordered_map>
#include <memory>

#include "gameobject.h"

class GameObject;

class ColliderManaged;

class ColliderManager {
private:
    std::unordered_map<int, std::shared_ptr<ColliderManaged>> collidersById;
public:
    ColliderManager();
    void subscribe(int id, std::shared_ptr<ColliderManaged> collider);
    void unsubscribe(int id);
    void notify();
    virtual ~ColliderManager() = default;
};


class ColliderManaged : virtual public GameObject, public std::enable_shared_from_this<ColliderManaged> {
private:
    std::weak_ptr<ColliderManager> cm;
public:
    ColliderManaged(std::weak_ptr<ColliderManager> cm): cm(cm) {}
    void init() override {
        cm.lock()->subscribe(id, shared_from_this());
    }
    virtual int getColliderTypeId() = 0;
    virtual void onCollision(std::shared_ptr<ColliderManaged> other) {
        (void)other;
    }
    virtual Point getSize() = 0;
    virtual ~ColliderManaged() {
        if(std::shared_ptr<ColliderManager> c = cm.lock()) {
            c->unsubscribe(id);
        }
    }
};