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

    Sudoku s = generateSudoku();
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            w.set_field(i, j, s[i][j]);
        }
    }
    

    return app.exec();
}
