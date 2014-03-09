#include <iostream>

#include "inputthread.h"

InputThread::InputThread(QObject *parent) :
    QThread(parent)
{
    devManager.scanDevices();
}

void InputThread::padReceiver(int id, Event::Type event, int value, void *object)
{
    std::cout << "Receiving pad signal: " << id << " " << value << std::endl;
    if(object){
        InputThread *in = static_cast<InputThread *>(object);

        if(id == 0){
            // value change, no id
            return;
        }

        id = id - in->PAD_OFFSET;
        if(id < 1){
            // invalid pad
            return;
        }

        emit in->setPad(event == Event::NOTEON);

    }else{
        std::cerr << "Error with object" << std::endl;
    }
}

void InputThread::sliderReceiver(int id, int value, void *object)
{
    if(object){
        InputThread *in = static_cast<InputThread *>(object);
        emit in->setSlider(value);
    }
}

void InputThread::run()
{
    DeviceManager::iterator dev;
    for(dev=devManager.begin(); dev!=devManager.end(); dev++){
        (*dev)->print();
        (*dev)->setPadReceiver(&InputThread::padReceiver, this);
        (*dev)->setSliderReceiver(&InputThread::sliderReceiver, this);
    }

    devManager.loop();
    getchar();
}
