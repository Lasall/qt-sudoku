#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

 public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	void set_field(int x, int y, int value = 0);

 private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H