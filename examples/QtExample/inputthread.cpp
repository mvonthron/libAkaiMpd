#include <iostream>

#include "inputthread.h"

InputThread::InputThread(QObject *parent) :
    QThread(parent)
{
    devManager.scanDevices();
}

void InputThread::padReceiver(int id, Event::Type event, int value, void *object)
{

    static int lastPadAccessed = 1;
    static int lastValue = 0;

    if(!object){
        std::cerr << "Error with object" << std::endl;
        return;
    }

    InputThread *in = static_cast<InputThread *>(object);

    if(id == 0){
        // value change, no id
        return;
    }

    int pad = id - InputThread::PAD_OFFSET;

    if(pad < 1){
        // invalid pad
        return;
    }

    std::cout << "Receiving pad signal: " << pad << " " << value << std::endl;
    emit in->setPadStatus(pad, event == Event::NOTEON);


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
    Device *mpd = devManager.getDeviceByName("Akai MPD18");
    if(!mpd){
        emit log("Failed to open Akai MPD18");
        return;
    }else{
        emit log("Akai MPD18 opened successfully");
        mpd->setPadReceiver(&InputThread::padReceiver, this);
        mpd->setSliderReceiver(&InputThread::sliderReceiver, this);
    }

    devManager.loop();
    getchar();
}
