#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class Window : public QWidget {
 public:
    explicit Window(QWidget *parent = 0);
};

#endif // WINDOW_H