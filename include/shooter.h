#pragma once

#include "entity.h"
#include "bullet.h"

class Shooter : virtual public Entity {
private:
    int dy;
    int timeoutFrameCount;
    int framesToFire = 0;
private:
    Point getSelfTopCenter() {
        return {
            getPosition().x + getSize().x / 2,
            getPosition().y
        };
    }
    Point getSelfBottomCenter() {
        return {
            getPosition().x + getSize().x / 2,
            getPosition().y + getSize().y
        };
    }
public:
    Shooter(int bulletsDy, int timeoutFrameCount = 3):
        dy(bulletsDy),
        timeoutFrameCount(timeoutFrameCount) {}
    void beforeUpdate() override {
        if(framesToFire != 0) {
            --framesToFire;
        }
    }
    void tryShoot() {
        if(framesToFire > 0) {
            return;
        }
        framesToFire = timeoutFrameCount;
        Point pos;
        if(dy < 0) {
            pos = getSelfTopCenter() + Point{0, -1};
        }
        else {
            pos = getSelfBottomCenter() + Point{0, 1};
        }
        game.lock()->createObject<Bullet>(pos, dy);
    }
};