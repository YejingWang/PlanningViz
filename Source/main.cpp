/***************************************************
* Author: YejingWang
* Date: 2021/08/11
****************************************************/

#include "QtWidgets/QApplication"
#include "QtCore/QCommandLineParser"
#include "QtCore/QCommandLineOption"

#include "MainWindow.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("YejingWang");
    QCoreApplication::setApplicationName("PlanningVis");
    QCoreApplication::setApplicationVersion("1.10");

    MainWindow window;
    window.show();
    return app.exec();
}
