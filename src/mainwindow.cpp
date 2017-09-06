#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "line_solver.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), s(Sudoku()) {
    ui->setupUi(this);

    connect(ui->button_solve, SIGNAL(released()), this, SLOT(solve()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::read(const Sudoku& s) {
    this->s = s;
    update();
}

void MainWindow::update() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            set_field(i, j, s[i][j]);
        }
    }
}

void MainWindow::solve() {
    LineSolver ls;
    ls.solve(s);
    update();
}

void MainWindow::set_field(int x, int y, int value) {
    if (value == 0)
        return;
    switch (y * 10 + x) {
        case 0:  ui->label_00->setText(QString::number(value)); break;
        case 1:  ui->label_01->setText(QString::number(value)); break;
        case 2:  ui->label_02->setText(QString::number(value)); break;
        case 3:  ui->label_03->setText(QString::number(value)); break;
        case 4:  ui->label_04->setText(QString::number(value)); break;
        case 5:  ui->label_05->setText(QString::number(value)); break;
        case 6:  ui->label_06->setText(QString::number(value)); break;
        case 7:  ui->label_07->setText(QString::number(value)); break;
        case 8:  ui->label_08->setText(QString::number(value)); break;
        case 10: ui->label_10->setText(QString::number(value)); break;
        case 11: ui->label_11->setText(QString::number(value)); break;
        case 12: ui->label_12->setText(QString::number(value)); break;
        case 13: ui->label_13->setText(QString::number(value)); break;
        case 14: ui->label_14->setText(QString::number(value)); break;
        case 15: ui->label_15->setText(QString::number(value)); break;
        case 16: ui->label_16->setText(QString::number(value)); break;
        case 17: ui->label_17->setText(QString::number(value)); break;
        case 18: ui->label_18->setText(QString::number(value)); break;
        case 20: ui->label_20->setText(QString::number(value)); break;
        case 21: ui->label_21->setText(QString::number(value)); break;
        case 22: ui->label_22->setText(QString::number(value)); break;
        case 23: ui->label_23->setText(QString::number(value)); break;
        case 24: ui->label_24->setText(QString::number(value)); break;
        case 25: ui->label_25->setText(QString::number(value)); break;
        case 26: ui->label_26->setText(QString::number(value)); break;
        case 27: ui->label_27->setText(QString::number(value)); break;
        case 28: ui->label_28->setText(QString::number(value)); break;
        case 30: ui->label_30->setText(QString::number(value)); break;
        case 31: ui->label_31->setText(QString::number(value)); break;
        case 32: ui->label_32->setText(QString::number(value)); break;
        case 33: ui->label_33->setText(QString::number(value)); break;
        case 34: ui->label_34->setText(QString::number(value)); break;
        case 35: ui->label_35->setText(QString::number(value)); break;
        case 36: ui->label_36->setText(QString::number(value)); break;
        case 37: ui->label_37->setText(QString::number(value)); break;
        case 38: ui->label_38->setText(QString::number(value)); break;
        case 40: ui->label_40->setText(QString::number(value)); break;
        case 41: ui->label_41->setText(QString::number(value)); break;
        case 42: ui->label_42->setText(QString::number(value)); break;
        case 43: ui->label_43->setText(QString::number(value)); break;
        case 44: ui->label_44->setText(QString::number(value)); break;
        case 45: ui->label_45->setText(QString::number(value)); break;
        case 46: ui->label_46->setText(QString::number(value)); break;
        case 47: ui->label_47->setText(QString::number(value)); break;
        case 48: ui->label_48->setText(QString::number(value)); break;
        case 50: ui->label_50->setText(QString::number(value)); break;
        case 51: ui->label_51->setText(QString::number(value)); break;
        case 52: ui->label_52->setText(QString::number(value)); break;
        case 53: ui->label_53->setText(QString::number(value)); break;
        case 54: ui->label_54->setText(QString::number(value)); break;
        case 55: ui->label_55->setText(QString::number(value)); break;
        case 56: ui->label_56->setText(QString::number(value)); break;
        case 57: ui->label_57->setText(QString::number(value)); break;
        case 58: ui->label_58->setText(QString::number(value)); break;
        case 60: ui->label_60->setText(QString::number(value)); break;
        case 61: ui->label_61->setText(QString::number(value)); break;
        case 62: ui->label_62->setText(QString::number(value)); break;
        case 63: ui->label_63->setText(QString::number(value)); break;
        case 64: ui->label_64->setText(QString::number(value)); break;
        case 65: ui->label_65->setText(QString::number(value)); break;
        case 66: ui->label_66->setText(QString::number(value)); break;
        case 67: ui->label_67->setText(QString::number(value)); break;
        case 68: ui->label_68->setText(QString::number(value)); break;
        case 70: ui->label_70->setText(QString::number(value)); break;
        case 71: ui->label_71->setText(QString::number(value)); break;
        case 72: ui->label_72->setText(QString::number(value)); break;
        case 73: ui->label_73->setText(QString::number(value)); break;
        case 74: ui->label_74->setText(QString::number(value)); break;
        case 75: ui->label_75->setText(QString::number(value)); break;
        case 76: ui->label_76->setText(QString::number(value)); break;
        case 77: ui->label_77->setText(QString::number(value)); break;
        case 78: ui->label_78->setText(QString::number(value)); break;
        case 80: ui->label_80->setText(QString::number(value)); break;
        case 81: ui->label_81->setText(QString::number(value)); break;
        case 82: ui->label_82->setText(QString::number(value)); break;
        case 83: ui->label_83->setText(QString::number(value)); break;
        case 84: ui->label_84->setText(QString::number(value)); break;
        case 85: ui->label_85->setText(QString::number(value)); break;
        case 86: ui->label_86->setText(QString::number(value)); break;
        case 87: ui->label_87->setText(QString::number(value)); break;
        case 88: ui->label_88->setText(QString::number(value)); break;
        default:
            Q_ASSERT_X(1 == 0, "MainWindow::set_field", "out of scope");
            break;
    }
}