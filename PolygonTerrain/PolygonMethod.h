#pragma once
#include <vector>

class point2d
{
public:
    point2d(int _x, int _y) : x(_x), y(_y) {}
    int x;
    int y;
};

const int oriCW  = 1;
const int oriCCW = -1;
const int oriCollinear = 0;

double DotProduct(point2d v1, point2d v2)
{
    return v1.x*v2.x + v1.y*v2.y;
}

double CrossProduct(point2d v1, point2d v2)
{
    return v1.x*v2.y - v1.y*v2.x;
}

int IsOrientation(const std::vector<point2d>& polygon)
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
    if (sum > 0.0) { return  oriCW; }
    // CCW
    if (sum < 0.0) { return oriCCW; }

    // Collinear 
    return oriCollinear;
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

void SutherlandHodgman(std::vector<point2d>& clip_boundry, std::vector<point2d>& polygon)
{
    auto cn = clip_boundry.size();
    auto pn = polygon.size();

    std::vector<point2d> clip;
    for (size_t i = 0; i < cn; ++i)
    {
        auto e1 = clip_boundry[(i + 0) % cn];
        auto e2 = clip_boundry[(i + 1) % cn];
        int a1 = (e2.y - e1.y);
        int b1 = (e1.x - e2.x);
        int c1 = (-a1 * e1.x - b1 * e1.y);

        auto p2 = polygon.back();
        for (auto& p1 : polygon)
        {
            bool in1 = (a1*p1.x + b1 * p1.y + c1) < 0;
            bool in2 = (a1*p2.x + b1 * p2.y + c1) < 0;

            if (in1 && in2)
            {
                clip.emplace_back(p1);
            }
            else if (!in1 && in2)
            {
                clip.emplace_back(intersection_point(e1, e2, p1, p2));
            }
            else if (in1 && !in2)
            {
                clip.emplace_back(intersection_point(e1, e2, p2, p1));
                clip.emplace_back(p1);
            }

            p2 = p1;
        }
        polygon = std::move(clip);
    }
}
