/***************************************************
* Author: YejingWang
* Date: 2021/08/11
****************************************************/

#pragma once

struct Point
{
    Point(const double xx, const double yy) :
        x(xx),
        y(yy)
    {}

    Point(const Point& p) :
        x(p.x),
        y(p.y)
    {}

    double x;
    double y;

    const Point& operator=(const Point& p) {
        x = p.x;
        y = p.y;
    }

    bool operator==(const Point& p) {
        return x == p.x && y == p.y;
    }
};

struct Line
{
    Line(const Point& pt1, const Point& pt2) :
        p1(pt1),
        p2(pt2)
    {}

    Line(const double x1, const double y1, const double x2, const double y2) :
        p1(x1, y1),
        p2(x2, y2)
    {}

    Point p1;
    Point p2;
};
