#pragma once

#include <memory>

#include "spaceinvader.h"
#include "entity.h"
#include "colliderid.h"
#include "point.h"
#include "renderingprimitives.h"

#include <iostream>

class Enemy : public Entity,
              public std::enable_shared_from_this<Enemy>
{
public:
    Colors color;
    Enemy(std::shared_ptr<Game> g, int id):
        GameObject(g, id, {1, 1}),
        Entity(std::static_pointer_cast<SpaceInvaderGame>(g), ColliderId::ENEMY, 100, {5, 5}),
        color(SpriteManager::getRandomColor())
        {}

    std::unique_ptr<RenderRange> getPrimitives() const override {
        return sm.lock()->getCrab(color);
    }

    void init() override {
        ColliderManaged::initComponent(shared_from_this());
    }

};