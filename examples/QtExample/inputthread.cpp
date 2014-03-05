#include "inputthread.h"

InputThread::InputThread(QObject *parent) :
    QThread(parent)
{
    devManager.scanDevices();
}


void InputThread::run()
{
    DeviceManager::iterator dev;
    for(dev=devManager.begin(); dev!=devManager.end(); dev++){
        (*dev)->print();
    }

    devManager.loop();
    getchar();
}
