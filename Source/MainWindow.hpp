/***************************************************
* Author: YejingWang
* Date: 2021/08/11
****************************************************/

#pragma once

#include "QtWidgets/QMainWindow"
#include "QtCore/QObject"

class Map;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent*);

private slots:

private:
    void loadMap(const std::string& mapFile);

    void drawWalls(QPainter& painter);
    void drawObstacles(QPainter& painter);
    void drawStartAndGoal(QPainter& painter);

    QWidget* mCentralWidget;

    Map* mMap;

    QPointF mCenterPoint;

    QPointF mStart;
    QPointF mGoal;

    int mPointTextSize;

    bool mShowWallWidth;

    // split the screen to a grid of mMeshNum * mMeshNum size
    int mMeshNum;

    // width of margin on both sides combined by meshSize
    int mMeshMarginNum;
};
