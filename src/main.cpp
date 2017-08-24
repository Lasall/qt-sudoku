#ifdef _MSC_VER
#    pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif
#include <QApplication>
#include "mainwindow.h"
#include "sudoku.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    return app.exec();
}
