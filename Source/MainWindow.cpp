/***************************************************
* Author: YejingWang
* Date: 2021/08/11
****************************************************/

#include "MainWindow.hpp"
#include "Map.hpp"

#include "QtWidgets/qapplication.h"
#include "QtWidgets/qdesktopwidget.h"
#include "QtGui/qscreen.h"
#include "QtGui/qpainter.h"

#include <algorithm>

QPointF MovePointTo(const QPointF& pt, const QPointF& dst) {
    return pt + dst;
}

void MoveLineTo(QLineF& line, const QPointF& dst) {
    line.setPoints(MovePointTo(line.p1(), dst), MovePointTo(line.p2(), dst));
}

std::vector<QLineF> WallWithWidth(const QLineF& line, const double width) {
    std::vector<QLineF> wallEdges(4);
    if (line.x1() == line.x2()) {
        wallEdges[0] = QLineF(QPointF(line.x1() - width / 2, line.y1()), QPointF(line.x1() + width / 2, line.y1()));
        wallEdges[1] = QLineF(QPointF(line.x1() + width / 2, line.y1()), QPointF(line.x2() + width / 2, line.y2()));
        wallEdges[2] = QLineF(QPointF(line.x2() + width / 2, line.y2()), QPointF(line.x2() - width / 2, line.y2()));
        wallEdges[3] = QLineF(QPointF(line.x2() - width / 2, line.y2()), QPointF(line.x1() - width / 2, line.y1()));
    }
    else {
        double theta = std::atan2(line.y2() - line.y1(), line.x2() / line.x1());
        double xDiff = width / 2 * std::sin(theta);
        double yDiff = width / 2 * std::cos(theta);
        wallEdges[0] = QLineF(QPointF(line.x1() + xDiff, line.y1() - yDiff), QPointF(line.x1() - xDiff, line.y1() + yDiff));
        wallEdges[1] = QLineF(QPointF(line.x1() - xDiff, line.y1() + yDiff), QPointF(line.x2() - xDiff, line.y2() + yDiff));
        wallEdges[2] = QLineF(QPointF(line.x2() - xDiff, line.y2() + yDiff), QPointF(line.x2() + xDiff, line.y2() - yDiff));
        wallEdges[3] = QLineF(QPointF(line.x2() + xDiff, line.y2() - yDiff), QPointF(line.x1() + xDiff, line.y1() - yDiff));
    }

    return wallEdges;
}

MainWindow::MainWindow() :
    mCentralWidget(new QWidget()),
    mMap(new Map("D:/PlanningViz/test.json")),
    mStart(-300, 300),
    mGoal(300, -300),
    mPointTextSize(20),
    mShowWallWidth(false),
    mMeshNum(20),
    mMeshMarginNum(2)
{
    setCentralWidget(mCentralWidget);

    QRectF rect = QGuiApplication::primaryScreen()->availableGeometry();
    setFixedSize(rect.width(), rect.height());

    mCenterPoint.setX(rect.width() / 2);
    mCenterPoint.setY(rect.height() / 2);
}

MainWindow::~MainWindow()
{
    delete mMap;
    delete mCentralWidget;
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    drawWalls(painter);
    drawObstacles(painter);
    drawStartAndGoal(painter);
}

void MainWindow::drawWalls(QPainter& painter) {
    std::vector<Wall> walls = mMap->walls();
    QPainterPath wallsPath;
    for (auto& wall : walls) {
        MoveLineTo(wall.centerLine, mCenterPoint);
        wallsPath.moveTo(wall.centerLine.x1(), wall.centerLine.y1());
        wallsPath.lineTo(wall.centerLine.x2(), wall.centerLine.y2());
        if (mShowWallWidth) {
            std::vector<QLineF> wallEdges = WallWithWidth(wall.centerLine, wall.width);
            for (auto& wallEdge : wallEdges) {
                wallsPath.moveTo(wallEdge.x1(), wallEdge.y1());
                wallsPath.lineTo(wallEdge.x2(), wallEdge.y2());
            }
        }
    }

    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
    painter.drawPath(wallsPath);
}

void MainWindow::drawObstacles(QPainter& painter) {
}

void MainWindow::drawStartAndGoal(QPainter& painter) {
    painter.setFont(QFont("times", mPointTextSize));
    QPointF start = MovePointTo(mStart, mCenterPoint);
    QRectF startRect(start.x() - mPointTextSize / 2, start.y() - mPointTextSize / 2, mPointTextSize, mPointTextSize);
    painter.setPen(QPen(Qt::green));
    painter.drawText(startRect, Qt::AlignCenter, tr("x"));
    QPointF goal = MovePointTo(mGoal, mCenterPoint);
    QRectF goalRect(goal.x() - mPointTextSize / 2, goal.y() - mPointTextSize / 2, mPointTextSize, mPointTextSize);
    painter.setPen(QPen(Qt::blue));
    painter.drawText(goalRect, Qt::AlignCenter, tr("x"));
}

void MainWindow::loadMap(const std::string& mapFile) {
    if (mMap) {
        delete mMap;
    }
    mMap = new Map(mapFile);
    update();
}
