#pragma once

#include <memory>

#include "renderer.h"
#include "renderingprimitives.h"


class Game;


class GameObject : public Renderable
{
private:
    std::weak_ptr<Game> game;
    Point pos;
    Point posToBeSet;
public:
    int id;

private:
    virtual void beforeUpdate() {};
    virtual void onDestroy() {};
protected:
    void setPosition(Point newPos);
public:
    GameObject() {}
    GameObject(std::weak_ptr<Game> g, int id, Point p = {0, 0});
    virtual void init() {}
    Point getPosition() const override;
    std::unique_ptr<RenderRange> getPrimitives() const override;
    void update();
    void destroy();
    virtual ~GameObject() = default;
};
