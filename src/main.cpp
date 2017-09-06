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

    for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 9; i++) {

            w.set_field(j, i, 1);
        }
    }
    

    return app.exec();
}
