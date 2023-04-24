#include <iostream>
#include <vector>
#include <math.h>

struct Point {
    float x;
    float y;

    bool operator==(const Point other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Point other) const {
        return !(*this == other);
    }
    Point operator+(const Point other) const {
        return {x + other.x, y + other.y};
    }
    Point operator-(const Point other) const {
        return {x - other.x, y - other.y};
    }
};

float angleFromTo(Point anchor, Point p1) {
    return atan2(p1.y - anchor.y, p1.x - anchor.x);
}

class AngleCmp {
private:
    Point anchor;

public:
    AngleCmp(Point anchor) {
        this->anchor = anchor;
    }
    bool operator()(const Point p1, const Point p2) const {
        if (p1 == anchor) {
            return true;
        }
        else if (p2 == anchor) {
            return false;
        }
        return angleFromTo(anchor, p1) < angleFromTo(anchor, p2);
    }
};

bool isPositiveOrientation(Point p1, Point p2) {
    return (p1.x * p2.y - p1.y * p2.x) >= 0;
}   

// Assumes there are no repeated points
std::vector<Point> convexHull(std::vector<Point> points) {
    if (points.size() <= 3) {
        return points;
    }

    std::vector<Point> hull;
    // Get anchor : point with smallest y-value
    Point anchor = points[0];
    for (int i = 1; i < points.size(); i++) {
        if (points[i].y < anchor.y) {
            anchor = points[i];
        }
    }

    // Sort by angle from anchor
    std::sort(points.begin(), points.end(), AngleCmp(anchor));
    
    hull.push_back(points[0]);
    hull.push_back(points[1]);
    // Check if point i should be in the hull
    for (int i = 2; i < points.size(); i++) {
        Point firstPoint = hull[hull.size() - 2];
        Point secondPoint = hull[hull.size() - 1];
        if (!isPositiveOrientation(secondPoint - firstPoint, points[i] - secondPoint)) {
            hull.erase(hull.end() - 1);
        }
        hull.push_back(points[i]);
    }

    return hull;
}

int main() {
    std::vector<Point> points = {
        {2, 3},
        {5, 3},
        {8, 1},
        {4, 2},
        {-1, 4},
        {-2,-1},
        {9,2},
        {-6,-4},
        {2,-2},
        {-2,-3},
        {-4, 1},
        {0, 0}
    };

    std::vector<Point> hull = convexHull(points);
    
    std::cout << "HULL" << std::endl;
    for (Point p : hull) {
        std::cout << p.x << " " << p.y << std::endl;
    }
    
}