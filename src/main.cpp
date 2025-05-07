#include "spaceinvader.h"
#include "player.h"
#include <unistd.h>
#include <atomic>
#include <csignal>
#include <ncurses.h>

std::atomic<bool> sigint;

int main()
{
    std::signal(SIGINT, [](int signal) {
        (void)signal;
        sigint = true;
    });
    std::shared_ptr<SpaceInvaderGame> game = 
        std::make_shared<SpaceInvaderGame>(std::make_unique<CLIRenderer>());
    game->createObject<Player>();
    while(!sigint) {
        game->update();
    }


    // initscr();
    // nodelay(stdscr, TRUE);
    // timeout(10);
    // bool f = false;
    // while(int a = getch()) {
    //     if(a != ERR || f) {d
    //         f = true;
    //         std::cout << a << std::endl;
    //     }
    // }
    // endwin();
    // return 0;
}