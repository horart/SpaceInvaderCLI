#include <ncurses.h>

#include "renderingprimitives.h"
#include "clirenderer.h"

const std::map<Colors, short> CLIRenderer::colorToCLIColor = {
    {
        {Colors::WHITE, COLOR_WHITE},
        {Colors::BLACK, COLOR_BLACK},
        {Colors::BLUE, COLOR_BLUE},
        {Colors::GREEN, COLOR_GREEN},
        {Colors::PURLE, COLOR_MAGENTA},
        {Colors::RED, COLOR_RED},
        {Colors::YELLOW, COLOR_YELLOW},
    },
};

CLIRenderer::CLIRenderer() {
    initscr();
    start_color();
    curs_set(0);
    nodelay(stdscr, TRUE);
    getmaxyx(stdscr, maxY, maxX);
}

void CLIRenderer::moveToPoint(Point pos) {
    move(pos.y, pos.x);
}

void CLIRenderer::chooseColor(Colors fg, Colors bg) {
    init_pair(1, colorToCLIColor.at(fg), colorToCLIColor.at(bg));
    attron(COLOR_PAIR(1));
}

void CLIRenderer::renderPrimitive(const RenderingCell& cell, Point pos) {
    moveToPoint(pos + cell.pos);
    chooseColor(Colors::BLACK, cell.color);
    printw(" ");
    refresh();
}
void CLIRenderer::renderPrimitive(const RenderingText& text, Point pos) {
    moveToPoint(pos + text.pos);
    chooseColor(text.color, text.bgColor);
    printw("%s", text.text.c_str());
    refresh();
}

CLIRenderer::~CLIRenderer() {
    endwin();
}