#pragma once

#include <memory>
#include <vector>
#include <random>

#include "point.h"
#include "renderingprimitives.h"

class SpriteManager {
private:
    inline static const std::vector<Point> crab_sprite_points = {
        // Row 0 (y=0)
        {3,0}, {7,0},
        // Row 1 (y=1)
        {4,1}, {6,1},
        // Row 2 (y=2)
        {3,2}, {4,2}, {5,2}, {6,2}, {7,2},
        // Row 3 (y=3)
        {2,3}, {3,3}, {5,3}, {7,3}, {8,3},
        // Row 4 (y=4) - Widest part
        {1,4}, {2,4}, {3,4}, {4,4}, {5,4}, {6,4}, {7,4}, {8,4}, {9,4},
        // Row 5 (y=5)
        {1,5}, {2,5}, {3,5}, {4,5}, {5,5}, {6,5}, {7,5}, {8,5}, {9,5},
        // Row 6 (y=6)
        {1,6}, {2,6}, {8,6}, {9,6},
        // Row 7 (y=7)
        {3,7}, {4,7}, {6,7}, {7,7}
    };
    inline static const std::vector<Point> player_sprite_points = {
        // Row 0 (y=0)
        {4,0}, {5,0}, {6,0},
        // Row 1 (y=1)
        {3,1}, {4,1}, {5,1}, {6,1}, {7,1},
        // Row 2 (y=2)
        {2,2}, {3,2}, {4,2}, {5,2}, {6,2}, {7,2}, {8,2},
        // Row 3 (y=3)
        {1,3}, {2,3}, {3,3}, {4,3}, {5,3}, {6,3}, {7,3}, {8,3}, {9,3},
        // Row 4 (y=4)
        {0,4}, {1,4}, {2,4}, {3,4}, {4,4}, {5,4}, {6,4}, {7,4}, {8,4}, {9,4}, {10,4}
    };
public:
    static Colors getRandomColor() {
        return static_cast<Colors>(std::rand() % static_cast<int>(Colors::BLACK));
    }
    Point getCrabSize() const {
        return {10, 8};
    }
    std::unique_ptr<RenderRange> getCrab(Colors color) const {
        return std::make_unique<CellsRange>(crab_sprite_points, color);
    }
    Point getPlayerSize() const {
        return {10, 5};
    }
    std::unique_ptr<RenderRange> getPlayer() const {
        return std::make_unique<CellsRange>(player_sprite_points, Colors::GREEN);
    }
};