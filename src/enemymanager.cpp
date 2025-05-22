#include <random>

#include "enemymanager.h"
#include "enemy.h"

void EnemyManager::subscribe(int id, std::shared_ptr<EnemyManaged> sub) {
    enemiesById[id] = sub;
}
void EnemyManager::unsubscribe(int id) {
    enemiesById.erase(id);
}std::unordered_map<int, std::weak_ptr<EnemyManaged>> enemiesById;

void EnemyManager::notify() {
    if(frameCounter == moveFreq) {
        frameCounter = 0;
    }
    else {
        ++frameCounter;
        return;
    }
    EnemyMovement movement;
    do {
        movement = static_cast<EnemyMovement>(std::rand() % 3 + 1);
    } while((movement == EnemyMovement::LEFT && blockLeft)
         || (movement == EnemyMovement::RIGHT && blockRight));

    if(movement == EnemyMovement::RIGHT) {
        blockLeft = false;
    }
    if(movement == EnemyMovement::LEFT) {
        blockRight = false;
    }
    if(movement == EnemyMovement::DOWN) {
        ++cellsCounter;
        if(cellsCounter == cellsToMoveBeforeSpawn) {
            cellsCounter = 0;
        }
    }
    for(auto& [id, wEnemy] : enemiesById) {
        std::shared_ptr<EnemyManaged> enemy = wEnemy.lock();
        enemy->move(movement);

        int enemyLeft = enemy->getPosition().x;
        int enemyRight = (enemy->getPosition() + enemy->getSize()).x;

        if(enemyLeft - enemy->getSize().x < 0) {
            blockLeft = true;
        }
        if(enemyRight + enemy->getSize().x >= game->getGameSize().x) {
            blockRight = true;
        }
    }

    if(cellsCounter == 0) {
        int chance = std::rand() % 100;
        if(chance < spawnChancePercent) {
            int enemiesCount = std::rand() % maxEnemiesToCreate + 1;
            spawnEnemies(enemiesCount);
            ++cellsCounter;
        }
        else {
            --cellsCounter;
        }
    }
}

void EnemyManager::spawnEnemies(int enemiesCount) {
    Point pos = {std::rand() % game->getGameSize().x/3, 0};
    for(int i = 0; i < enemiesCount; ++i) {
        auto spawned = game->createObject<Enemy>(pos);
        pos.x += spawned->getSize().x + std::rand() % 4;
    }
}