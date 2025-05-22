#include "spaceinvader.h"
#include "player.h"

void SpaceInvaderGame::init() {
    createObject<Player>();
    enemyManager->spawnEnemies(7);
    scoreObject = createObject<Score>(Point{0, getGameSize().y - 1}).get();
}

std::unique_ptr<RenderRange> GameOver::getPrimitives() const {
    return std::static_pointer_cast<SpaceInvaderGame>(game.lock())->spriteManager->getGameOver();
}