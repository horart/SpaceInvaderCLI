#include <ncurses.h>
#include <chrono>

#include "cliinputmanager.h"

CLIInputManager::CLIInputManager(std::chrono::duration<int, std::milli> timeout) {
    timeout(timeout.count());
    noecho();
}

void CLIInputManager::setTimeout(std::chrono::duration<int, std::milli> timeout) {
    timeout(timeout.count());
}

char CLIInputManager::getInput() {
    flushinp();
    int c = getch();
    return c != ERR? c : 0;
}