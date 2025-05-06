#pragma once

#include <string>

#include "point.h"


class Renderer;

enum class Colors : int {
    WHITE,
    RED,
    GREEN,
    YELLOW,
    PURLE,
    BLUE,
    BLACK,
};

class RenderingPrimitive {
public:
    Point pos;
public:
    virtual void accept(Renderer&, Point pos) const = 0;
    virtual ~RenderingPrimitive() {}
};

class RenderingCell : public RenderingPrimitive {
public:
    Colors color;
public:
    RenderingCell(Point pos, Colors color);

    void accept(Renderer& renderer, Point pos) const override;
};

class RenderingText : public RenderingPrimitive {
public:
    Colors color;
    Colors bgColor;
    std::string text;
public:
    RenderingText(Point pos, Colors fg, Colors bg, std::string text);

    void accept(Renderer& renderer, Point pos) const override;
};