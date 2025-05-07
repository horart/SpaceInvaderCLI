#pragma once

#include <memory>

#include "spaceinvader.h"
#include "entity.h"
#include "colliderid.h"
#include "inputmanager.h"
#include "point.h"

#include <iostream>

class Player : public Entity,
               public InputManaged,
               public std::enable_shared_from_this<Player>
{
private:
    static Point getBottomCenter(Point gameSize, Point size) {
        return {
            (gameSize.x - size.x) / 2,
            gameSize.y - size.y
        };
    }
public:
    Player(std::shared_ptr<Game> g, int id):
        GameObject(g, id, getBottomCenter(g->getGameSize(), 
                std::static_pointer_cast<SpaceInvaderGame>(g)->spriteManager->getPlayerSize())),
        Entity(std::static_pointer_cast<SpaceInvaderGame>(g), ColliderId::PLAYER, 100, 
                std::static_pointer_cast<SpaceInvaderGame>(g)->spriteManager->getPlayerSize()),
        InputManaged(std::static_pointer_cast<SpaceInvaderGame>(g)->inputManager) 
        {}

    std::unique_ptr<RenderRange> getPrimitives() const override {
        return sm.lock()->getPlayer();
    }

    void init() override {
        InputManaged::initComponent(shared_from_this());
        ColliderManaged::initComponent(shared_from_this());
    }

    void onInput(char c) override;

    void onCollision(std::shared_ptr<ColliderManaged> other) override {
        if(other->getColliderTypeId() == static_cast<int>(ColliderId::ENEMY)) {
            if(!makeDamage(100)) {
                destroy();
            }
        }
    }

    ~Player() = default;
};