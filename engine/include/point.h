#pragma once

struct Point {
    int x;
    int y;
    Point() = default;
    Point(int x, int y): x(x), y(y) {}
    Point operator +() const {
        return *this;
    }
    Point operator +(const Point& rhs) const {
        return {x + rhs.x, y + rhs.y};
    }
    Point operator -() const {
        return {-x, -y};
    }
    Point& operator +=(const Point& other) {
        return *this = *this + other;
    }
    Point operator -(const Point& rhs) const {
        return *this + (-rhs);
    }
    Point& operator -=(const Point& other) {
        return *this = *this - other;
    }
    bool operator ==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    bool operator !=(const Point& other) const {
        return !(*this == other);
    }
};