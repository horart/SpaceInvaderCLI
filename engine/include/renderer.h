#pragma once

#include <memory>
#include <vector>

#include "point.h"
#include "renderingprimitives.h"


class Renderable {
public:
    virtual std::shared_ptr<std::vector<std::shared_ptr<RenderingPrimitive>>> getPrimitives() const = 0;
    virtual Point getPosition() const = 0;
    virtual ~Renderable() {}
};


class Renderer {
public:
    virtual void renderPrimitive(const RenderingCell&, Point pos) = 0;
    virtual void renderPrimitive(const RenderingText&, Point pos) = 0;
    
    Renderer() = default;
    Renderer(const Renderer&) = delete;
    void render(Renderable& renderable) {
        if(!renderable.getPrimitives()) {
            return;
        }
        Point pos = renderable.getPosition();
        for(std::shared_ptr<const RenderingPrimitive> prim : *renderable.getPrimitives()) {
            prim->accept(*this, pos);
        }
    }
    Renderer& operator=(const Renderer&) = delete;
    virtual ~Renderer() {}
};