#pragma once
#include <memory>

namespace prototype
{
struct Point
{
    int x{ 0 }, y{ 0 };

    Point() {}

    Point(const int x, const int y) : x{ x }, y{ y } {}
};

struct Line
{
    Point* start, * end;

    Line(Point* const start, Point* const end)
        : start(start), end(end)
    {
    }

    ~Line()
    {
        delete start;
        delete end;
    }

    Line deep_copy() const
    {
        // TODO
        Point* nstart = new Point(start->x, start->y);
        Point* nend = new Point(end->x, end->y);
        return Line{nstart, nend};
    }
};
}