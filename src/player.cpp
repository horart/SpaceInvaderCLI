#include "player.h"
#include "bullet.h"

void Player::onInput(char c)  {
    switch (c) {
        case 'a':
            if(getPosition().x > 0) {
                setPosition(getPosition() + Point{-1, 0});
            }
            break;
        case 'd':
            if(getPosition().x < game.lock()->getGameSize().x - getSize().x - 1) {
                setPosition(getPosition() + Point{1, 0});
            }
            break;
        case ' ':
            tryShoot();
            break;
        default:
            break;
    }
}


void Player::onCollision(std::shared_ptr<ColliderManaged> other) {
    if(other->getColliderTypeId() == static_cast<int>(ColliderId::ENEMY)) {
        if(!makeDamage(100)) {
            destroy();
        }
    }
    if(other->getColliderTypeId() == static_cast<int>(ColliderId::BULLET)) {
        if(!makeDamage(20)) {
            destroy();
        }
    }
}

Point Player::getGameBottomCenter(Point gameSize, Point size) {
    return {
        (gameSize.x - size.x) / 2,
        gameSize.y - size.y
    };
}