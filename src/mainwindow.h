#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sudoku.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

 public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    MainWindow(const MainWindow&) = delete;
    MainWindow operator=(const MainWindow&) = delete;

    void read(const Sudoku& s);
    void update();

 private slots:
    void solve();

 private:
    Ui::MainWindow *ui;
    Sudoku s;

    void set_field(int x, int y, int value);
};

#endif  // MAINWINDOW_H