#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(InputThread *t, QWidget *parent) :
    inThread(t), QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /** fill a pushbuttons array to emulate a (very) quick and dirty QSignalMapper
     */
    pads[0] = ui->pad1;
    pads[1] = ui->pad2;
    pads[2] = ui->pad3;
    pads[3] = ui->pad4;
    pads[4] = ui->pad5;
    pads[5] = ui->pad6;
    pads[6] = ui->pad7;
    pads[7] = ui->pad8;
    pads[8] = ui->pad9;
    pads[9] = ui->pad10;
    pads[10] = ui->pad11;
    pads[11] = ui->pad12;
    pads[12] = ui->pad13;
    pads[13] = ui->pad14;
    pads[14] = ui->pad15;
    pads[15] = ui->pad16;


    connect(inThread, SIGNAL(setPadStatus(int,bool)), this, SLOT(updateButtonStatus(int,bool)));
    connect(inThread, SIGNAL(setPadValue(int,int)), this, SLOT(updateButtonStatus(int,int)));

    connect(inThread, SIGNAL(setSlider(int)), ui->slider, SLOT(setValue(int)));
    connect(inThread, SIGNAL(log(QString)), ui->statusBar, SLOT(showMessage(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::loop()
{
}

void MainWindow::updateButtonStatus(int pad, bool onOff)
{
    if(pad < 1 || pad > 16){
        ui->statusBar->showMessage(QString("Invalid pad number %0").arg(pad));
    }
    else {
        ui->statusBar->showMessage(QString("Event on pad %0").arg(pad));
        pads[pad-1]->setChecked(onOff);

    }
}

void MainWindow::updateButtonValue(int pad, int value)
{
    if(pad < 1 || pad > 16){
        ui->statusBar->showMessage(QString("Invalid pad number %0").arg(pad));
    }
    else {
        if(value == 0){
            pads[pad-1]->setText(QString("PAD %0").arg(pad));
        }else{
            pads[pad-1]->setText(QString("%0").arg(value));
        }


    }
}
