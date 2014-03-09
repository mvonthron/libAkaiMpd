#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "inputthread.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(InputThread *t, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateButtonStatus(int pad, bool onOff);
    void updateButtonValue(int pad, int value);

private:
    Ui::MainWindow *ui;
    InputThread *inThread;
    QPushButton *pads[16];
};

#endif // MAINWINDOW_H
