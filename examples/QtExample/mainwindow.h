#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

    void loop();

private:
    Ui::MainWindow *ui;
    InputThread *inThread;
};

#endif // MAINWINDOW_H
