#include <ncurses.h>

#include "cliinputmanager.h"

char CLIInputManager::getInput() {
    flushinp();
    int c = getch();
    return c ? c != ERR : 0;
}