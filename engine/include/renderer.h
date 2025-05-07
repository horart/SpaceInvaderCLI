#pragma once

#include <memory>

#include "point.h"
#include "renderingprimitives.h"


class Renderable {
public:
    virtual std::unique_ptr<RenderRange> getPrimitives() const = 0;
    virtual Point getPosition() const = 0;
    virtual ~Renderable() {}
};


class Renderer {
public:
    virtual void renderPrimitive(const RenderingCell&, Point pos) = 0;
    virtual void renderPrimitive(const RenderingText&, Point pos) = 0;
    virtual void flush() = 0;
    virtual void clear() = 0;
    virtual Point getGameSize() const = 0;

    Renderer() = default;
    Renderer(const Renderer&) = delete;
    void render(Renderable& renderable) {
        if(!renderable.getPrimitives()) {
            return;
        }
        Point pos = renderable.getPosition();
        std::unique_ptr<RenderRange> range = renderable.getPrimitives();
        for(auto it = range->begin(), end = range->end(); *it != *end; ++*it) {
            auto prim = **it;
            prim->accept(*this, pos);
        }
    }
    Renderer& operator=(const Renderer&) = delete;
    virtual ~Renderer() {}
};