#include <string>

#include "point.h"
#include "renderer.h"
#include "renderingprimitives.h"


RenderingCell::RenderingCell(Point pos, Colors color) {
    this->pos = pos;
    this->color = color;
}

void RenderingCell::accept(Renderer& renderer, Point pos) const {
    renderer.renderPrimitive(*this, pos);
}




RenderingText::RenderingText(Point pos, Colors fg, Colors bg, std::string text) {
    this->pos = pos;
    this->color = fg;
    this->bgColor = bg;
    this->text = text;
}

void RenderingText::accept(Renderer& renderer, Point pos) const {
    renderer.renderPrimitive(*this, pos);
}