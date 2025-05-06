#include "spaceinvader.h"
#include "player.h"
#include <unistd.h>

int main()
{
    std::shared_ptr<SpaceInvaderGame> game = std::make_shared<SpaceInvaderGame>();
    game->createObject<Player>();
    game->update();
}