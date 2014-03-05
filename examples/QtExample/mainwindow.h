#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "devicemanager.hpp"
#include "device.hpp"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void loop();

private:
    Ui::MainWindow *ui;
    DeviceManager devManager;
};

#endif // MAINWINDOW_H
