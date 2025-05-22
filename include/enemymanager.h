#pragma once

#include <unordered_map>
#include <memory>

#include "gameobject.h"
#include "game.h"
#include "collidermanager.h"

class GameObject;

class EnemyManaged;

enum class EnemyMovement {
    LEFT = 1,
    RIGHT,
    DOWN
};

class EnemyManager {
private:
    std::unordered_map<int, std::weak_ptr<EnemyManaged>> enemiesById;
    Game* game;
    bool blockLeft = false;
    bool blockRight = false;
    
    int moveFreq = 30;
    int frameCounter = 0;

    int spawnChancePercent = 70;
    int cellsToMoveBeforeSpawn = 8;
    int cellsCounter = 1;
    
    int maxEnemiesToCreate = 6;
public:
    EnemyManager(Game* game): game(game) {}
    void subscribe(int id, std::shared_ptr<EnemyManaged> sub);
    void unsubscribe(int id);
    void notify();
    void spawnEnemies(int enemiesCount);
    virtual ~EnemyManager() = default;
};


class EnemyManaged : virtual public ColliderManaged {
private:
    std::weak_ptr<EnemyManager> cm;
public:
    EnemyManaged() {}
    EnemyManaged(std::weak_ptr<EnemyManager> cm): cm(cm) {}
    void initComponent(std::shared_ptr<EnemyManaged> self) {
        cm.lock()->subscribe(id, self);
    }
    virtual void move(EnemyMovement where) {
        switch(where) {
            case EnemyMovement::LEFT:
                setPosition(getPosition() + Point{-1, 0});
                break;
            case EnemyMovement::RIGHT:
                setPosition(getPosition() + Point{+1, 0});
                break;
            case EnemyMovement::DOWN:
                setPosition(getPosition() + Point{0, +1});
                break;
        }
    }
    virtual ~EnemyManaged() {
        if(std::shared_ptr<EnemyManager> c = cm.lock()) {
            c->unsubscribe(id);
        }
    }
};