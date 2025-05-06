#pragma once

#include <memory>

#include "spaceinvader.h"
#include "entity.h"
#include "colliderid.h"
#include "point.h"


class Player : public Entity {
public:
    Player(std::shared_ptr<Game> g, int id):
        Entity(std::static_pointer_cast<SpaceInvaderGame>(g), id, {1, 1}, ColliderId::PLAYER, 100, {5, 5}) {}

    std::shared_ptr<std::vector<std::shared_ptr<RenderingPrimitive>>> getPrimitives() const override {
        return sm.lock()->sprites;
    }
};