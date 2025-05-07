#pragma once

#include "renderer.h"
#include "renderingprimitives.h"
#include <map>

class CLIRenderer : public Renderer {
private:
    static const std::map<Colors, short> colorToCLIColor;
    int maxX;
    int maxY;
private:
    void moveToPoint(Point pos);
    void chooseColor(Colors fg, Colors bg);
public:
    CLIRenderer();

    void renderPrimitive(const RenderingCell&, Point pos) override;
    void renderPrimitive(const RenderingText&, Point pos) override;
    void clear() override;
    void flush() override;

    ~CLIRenderer();
};