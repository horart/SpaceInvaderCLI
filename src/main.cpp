#include "spaceinvader.h"
#include "player.h"
#include "enemy.h"
#include <unistd.h>
#include <atomic>
#include <csignal>
#include "shooter.h"

std::atomic<bool> sigint;
int main()
{
    std::signal(SIGINT, [](int signal) {
        (void)signal;
        sigint = true;
    });
    std::shared_ptr<SpaceInvaderGame> game = 
        std::make_shared<SpaceInvaderGame>(std::make_unique<CLIRenderer>());
    game->init();
    while(!sigint) {
        game->update();
    }
}