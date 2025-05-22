#pragma once

#include <memory>

#include "spaceinvader.h"
#include "entity.h"
#include "colliderid.h"
#include "point.h"
#include "renderingprimitives.h"

#include <iostream>

class Bullet : public Entity,
              public std::enable_shared_from_this<Bullet>
{
private:
    const int dy;
public:
    Bullet(std::shared_ptr<Game> g, int id, Point pos, int dy):
        GameObject(g, id, pos),
        ColliderManaged(std::static_pointer_cast<SpaceInvaderGame>(g)->colliderManager),
        Entity(std::static_pointer_cast<SpaceInvaderGame>(g), ColliderId::BULLET, 100,
        std::static_pointer_cast<SpaceInvaderGame>(g)->spriteManager->getBulletSize()),
        dy(dy) {}

    std::unique_ptr<RenderRange> getPrimitives() const override {
        return sm.lock()->getBullet();
    }
    void beforeUpdate() override {
        setPosition({getPosition().x, getPosition().y + dy});
        if(getPosition().y <= 0 || getPosition().y + getSize().y >= game.lock()->getGameSize().y) {
            destroy();
        }
    }
    void init() override {
        ColliderManaged::initComponent(shared_from_this());
    }
    void onCollision(std::shared_ptr<ColliderManaged> other) override {
        (void)other;
        destroy();
    }

};