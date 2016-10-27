#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow gui("3D Printer App", 1020, 650);
    gui.show();

    return app.exec();
}
