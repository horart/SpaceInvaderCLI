#include "enemy.h"

EnemyType unwrapRandom(EnemyType type) {
    if(type == EnemyType::RANDOM) {
        return static_cast<EnemyType>(std::rand() % 3 + 1);
    }
    return type;

}

std::unique_ptr<RenderRange> Enemy::getPrimitives() const {
    switch(type) {
        case EnemyType::CRAB:
            return sm.lock()->getCrab(color);
        case EnemyType::SQUID:
            return sm.lock()->getSquid(color);
        case EnemyType::OCTOPUS:
            return sm.lock()->getOctopus(color);
        default:
            throw std::invalid_argument("Invalid enemy type");
    }
}

Enemy::Enemy(std::shared_ptr<Game> g, int id, Point pos, EnemyType type) :
    GameObject(g, id, pos),
    ColliderManaged(std::static_pointer_cast<SpaceInvaderGame>(g)->colliderManager),
    Entity(std::static_pointer_cast<SpaceInvaderGame>(g), ColliderId::ENEMY, 100,
    {0, 0}),
    Shooter(1, 60),
    EnemyManaged(std::static_pointer_cast<SpaceInvaderGame>(g)->enemyManager),
    type(unwrapRandom(type)),
    color(SpriteManager::getRandomColor())
    {
        size = getSizeByType(sm.lock(), this->type);
    }

Point Enemy::getSizeByType(std::shared_ptr<SpriteManager> sm, EnemyType type) {
    switch(type) {
        case EnemyType::CRAB:
            return sm->getCrabSize();
        case EnemyType::SQUID:
            return sm->getSquidSize();
        case EnemyType::OCTOPUS:
            return sm->getOctopusSize();
        default:
            throw std::invalid_argument("Invalid enemy type");
    }
}