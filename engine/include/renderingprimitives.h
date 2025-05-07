#pragma once

#include <string>
#include <memory>
#include <vector>

#include "point.h"


class Renderer;

enum class Colors : int {
    WHITE = 0,
    RED,
    GREEN,
    YELLOW,
    PURLE,
    BLUE,
    BLACK,
    RANDOM
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


struct RenderIterator {
    size_t index;

    RenderIterator(size_t index = 0) : 
        index(index) {}

    virtual std::shared_ptr<RenderingPrimitive> operator*() = 0;

    RenderIterator& operator++() {
        ++index;
        return *this;
    }

    bool operator!=(const RenderIterator& other) const {
        return index != other.index;
    }
    bool operator==(const RenderIterator& other) const {
        return index == other.index;
    }

    virtual ~RenderIterator() = default;
};

struct PrimitivesIterator : public RenderIterator {
    const std::vector<std::shared_ptr<RenderingPrimitive>>& primitives;

    PrimitivesIterator(const std::vector<std::shared_ptr<RenderingPrimitive>>& p, size_t index = 0) : 
        RenderIterator(index),
        primitives(p) {}

    std::shared_ptr<RenderingPrimitive> operator*() override {
        return primitives[index];
    }
};

struct CellsIterator : public RenderIterator {
    const std::vector<Point>& points;
    Colors color;

    CellsIterator(const std::vector<Point>& p, Colors color, size_t index = 0) : 
        RenderIterator(index),
        points(p),
        color(color) {}

    std::shared_ptr<RenderingPrimitive> operator*() override {
        return std::make_shared<RenderingCell>(points[index], color);
    }
};


struct RenderRange {
    virtual std::unique_ptr<RenderIterator> begin() const = 0;
    virtual std::unique_ptr<RenderIterator> end() const = 0;
    virtual ~RenderRange() = default;
};

struct CellsRange : public RenderRange {
    const std::vector<Point>& points;
    Colors color;

    CellsRange(const std::vector<Point>& p, Colors color) : points(p), color(color) {}

    std::unique_ptr<RenderIterator> begin() const override {
        return std::make_unique<CellsIterator>(points, color);
    }

    std::unique_ptr<RenderIterator> end() const override {
        return std::make_unique<CellsIterator>(points, color, points.size());
    }
};

struct PrimitivesRange {
    const std::vector<std::shared_ptr<RenderingPrimitive>>& primitives;

    PrimitivesRange(const std::vector<std::shared_ptr<RenderingPrimitive>>& p) : primitives(p) {}

    std::unique_ptr<RenderIterator> begin() const {
        return std::make_unique<PrimitivesIterator>(primitives);
    }

    std::unique_ptr<RenderIterator> end() const {
        return std::make_unique<PrimitivesIterator>(primitives, primitives.size());
    }
};
