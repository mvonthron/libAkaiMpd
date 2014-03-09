#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

void sliderReceiver(int id, int value)
{
    std::cout << "Slider " << id << " value: " << value << std::endl;
}

MainWindow::MainWindow(InputThread *t, QWidget *parent) :
    inThread(t), QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(inThread, SIGNAL(setPad(bool)), ui->pad1, SLOT(setChecked(bool)));

    connect(inThread, SIGNAL(setSlider(int)), ui->slider, SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::loop()
{
}
