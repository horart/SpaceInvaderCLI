#pragma once

#include <memory>

#include "spaceinvader.h"
#include "entity.h"
#include "colliderid.h"
#include "inputmanager.h"
#include "point.h"
#include "shooter.h"

#include <iostream>

class Player :
               public InputManaged,
               public Shooter,
               public std::enable_shared_from_this<Player>
{
private:
    static Point getGameBottomCenter(Point gameSize, Point size);
public:
    Player(std::shared_ptr<Game> g, int id):
        GameObject(g, id, getGameBottomCenter(g->getGameSize(), 
                std::static_pointer_cast<SpaceInvaderGame>(g)->spriteManager->getPlayerSize())),
        ColliderManaged(std::static_pointer_cast<SpaceInvaderGame>(g)->colliderManager),
        Entity(std::static_pointer_cast<SpaceInvaderGame>(g), ColliderId::PLAYER, 100, 
               std::static_pointer_cast<SpaceInvaderGame>(g)->spriteManager->getPlayerSize()),
        InputManaged(std::static_pointer_cast<SpaceInvaderGame>(g)->inputManager),
        Shooter(-1, 3) {}

    std::unique_ptr<RenderRange> getPrimitives() const override {
        return sm.lock()->getPlayer();
    }

    void init() override {
        InputManaged::initComponent(shared_from_this());
        ColliderManaged::initComponent(shared_from_this());
    }

    void beforeUpdate() override {
        Shooter::beforeUpdate();
    }

    void onInput(char c) override;

    void onCollision(std::shared_ptr<ColliderManaged> other) override;

    ~Player() {
        std::static_pointer_cast<SpaceInvaderGame>(game.lock())->gameOver();
    }
};