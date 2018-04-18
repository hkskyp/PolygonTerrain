#pragma once
#include <vector>
#include <windows.h>

double DotProduct(POINT v1, POINT v2)
{
    return v1.x*v2.x + v1.y*v2.y;
}

double CrossProduct(POINT v1, POINT v2)
{
    return v1.x*v2.y - v1.y*v2.x;
}

int IsWindingDirection(const std::vector<POINT>& polygon)
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
