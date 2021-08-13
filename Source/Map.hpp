/***************************************************
* Author: YejingWang
* Date: 2021/08/11
****************************************************/

#pragma once

//#include "Geometry.hpp"

#include "QtCore/QLine.h"

#include <string>
#include <vector>

struct Wall {
    Wall(const double x1, const double y1, const double x2, const double y2, const double w) :
        centerLine(x1, y1, x2, y2),
        width(w)
    {}

    QLineF centerLine;
    double width;
};

struct Obstacle {
    enum class EObstacleType {
        ePolygon,
        eCircle
    };

    EObstacleType type;
};

struct PolyObstalce : public Obstacle {
    std::vector<QPointF> vertices;
    double width;
};

struct CircularObstacle : public Obstacle {
    QPointF center;
    double radius;
    double width;
};

class Map
{
public:
    Map(const std::string& mapFile);

    std::vector<Wall> walls() const;

    bool valid() const;

private:
    bool loadMap(const std::string& mapFile);

private:
    std::vector<Wall> mWalls;

    bool mValid;
};
