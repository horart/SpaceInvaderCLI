#pragma once

#include <memory>

#include "spaceinvader.h"
#include "entity.h"
#include "colliderid.h"
#include "point.h"
#include "renderingprimitives.h"
#include "enemymanager.h"
#include "shooter.h"

#include <iostream>

enum class EnemyType {
    RANDOM = 0,
    CRAB,
    SQUID,
    OCTOPUS
};

class Enemy :
              public Shooter,
              public EnemyManaged,
              public std::enable_shared_from_this<Enemy>
{
private:
    EnemyType type;
    std::unique_ptr<RenderRange> getPrimitivesByType(EnemyType type);
private:
    static Point getSizeByType(std::shared_ptr<SpriteManager> sm, EnemyType type);
public:
    Colors color;
    Enemy(std::shared_ptr<Game> g, int id, Point pos = {1, 1}, EnemyType type = EnemyType::RANDOM);

    std::unique_ptr<RenderRange> getPrimitives() const override;

    void init() override {
        ColliderManaged::initComponent(shared_from_this());
        EnemyManaged::initComponent(shared_from_this());
    }

    void beforeUpdate() override {
        if(getPosition().y + getSize().y >= game.lock()->getGameSize().y) {
            std::static_pointer_cast<SpaceInvaderGame>(game.lock())->gameOver();
        }
        Shooter::beforeUpdate();
        tryShoot();
    }

    void onCollision(std::shared_ptr<ColliderManaged> other) override {
        if(other->getColliderTypeId() == static_cast<int>(ColliderId::BULLET)) {
            if(!makeDamage(50)) {
                destroy();
            }
        }
    }

    void onDestroy() override {
        if(auto g = std::static_pointer_cast<SpaceInvaderGame>(game.lock())) g->addScore(10);
    }

};