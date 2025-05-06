#pragma once

#include "gameobject.h"
#include "collidermanager.h"
#include "colliderid.h"
#include "point.h"
#include "inputmanager.h"
#include "spaceinvader.h"

class Entity:
    public ColliderManaged
{
protected:
    int health;
    const ColliderId colliderId;
    Point size;
    std::weak_ptr<SpriteManager> sm;
protected:
    bool isAlive() {
        return health > 0;
    }
    // Returns true if the entity is alive after the blow
    bool makeDamage(int damage) {
        return (health -= damage) > 0;
    }
public:
    Entity(std::weak_ptr<SpaceInvaderGame> g, int id, Point p, 
            ColliderId colliderId,
            int health, Point size):
        GameObject(g, id, p),
        ColliderManaged(g.lock()->colliderManager),
        health(health),
        colliderId(colliderId),
        size(size),
        sm(g.lock()->spriteManager) {}
    int getColliderTypeId() override {
        return static_cast<int>(colliderId);
    }
    Point getSize() override {
        return size;
    }
};