#include <ncurses.h>

#include "cliinputmanager.h"

char CLIInputManager::getInput() {
    flushinp();
    int c = getch();
    return c != ERR? c : 0;
}