#pragma once

#include <memory>
#include <vector> // Added for std::vector

#include "point.h"
#include "renderingprimitives.h"

struct SpriteManager {
    // Relative coordinates for a crab sprite (11x8 pixels, Type A, Frame 1)
    // (0,0) is the top-left pixel of the crab's 11x8 bounding box.
    // Using inline static const for in-class initialization (C++17 and later)
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
    std::shared_ptr<std::vector<std::shared_ptr<RenderingPrimitive>>> sprites;
    SpriteManager() {
        sprites = std::make_shared<std::vector<std::shared_ptr<RenderingPrimitive>>>();
        for(const auto& point : crab_sprite_points) {
            sprites->emplace_back(std::make_shared<RenderingCell>(point, Colors::WHITE));
        }
    }
    SpriteManager(const SpriteManager&) = default;

    std::shared_ptr<std::vector<std::shared_ptr<RenderingPrimitive>>> crab() {
        return sprites;
    }
};