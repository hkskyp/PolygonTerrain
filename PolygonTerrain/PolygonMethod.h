#pragma once
#include <vector>

class point2d
{
public:
    int x;
    int y;
};

double DotProduct(point2d v1, point2d v2)
{
    return v1.x*v2.x + v1.y*v2.y;
}

double CrossProduct(point2d v1, point2d v2)
{
    return v1.x*v2.y - v1.y*v2.x;
}

int IsWindingDirection(const std::vector<point2d>& polygon)
{
    if (polygon.empty()) { return 0; }

    auto n = polygon.size();

    double sum = 0.0;
    for (auto i = 0ul; i < n; ++i)
    {
        auto j = (i + 1ul) % n;
        sum += (double)(polygon[j].x - polygon[i].x) * (double)(polygon[j].y + polygon[i].y);
    }

    // CW
    if (sum > 0.0) { return  1; }
    // CCW
    if (sum < 0.0) { return -1; }

    // Collinear 
    return 0;
}

point2d intersection_point(const point2d& p1, const point2d& p2, const point2d& p3, const point2d& p4)
{
    const int a1 = (p2.y - p1.y);
    const int b1 = (p1.x - p2.x);
    const int c1 = (-a1 * p1.x - b1 * p1.y);

    const int a2 = (p4.y - p3.y);
    const int b2 = (p3.x - p4.x);
    const int c2 = (-a2 * p3.x - b2 * p3.y);

    const float ratio = 1.0f / (b2 * a1 - b1 * a2);

    return { static_cast<int>((b1 * c2 - b2 * c1) * ratio), static_cast<int>((a2 * c1 - a1 * c2) * ratio) };

}