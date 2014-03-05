#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

void sliderReceiver(int id, int value)
{
    std::cout << "Slider " << id << " value: " << value << std::endl;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    devManager.scanDevices();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::loop()
{
    DeviceManager::iterator dev;
    for(dev=devManager.begin(); dev!=devManager.end(); dev++){
        (*dev)->print();
    }

    devManager.loop();
}
