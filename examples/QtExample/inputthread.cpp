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
    std::cout << "Receiving pad signal: " << id << ": " << value << " Type: " << Event::toString(event) << std::endl;

    if(!object){
        std::cerr << "Error with object" << std::endl;
        return;
    }

    InputThread *in = static_cast<InputThread *>(object);

    /** value change is tricky because no pad value is associated :(
     *  we have to remember which pad was accessed last, unfortunately
     *  this doesn't work well when several pads are touched at the same time
     */
    if(id == 0 && event == Event::VALUECHANGE){
        emit in->setPadValue(lastPadAccessed, value);

    }else{

        int pad = id - InputThread::PAD_OFFSET;
        if(pad < 1){
            // invalid pad
            return;
        }

        lastPadAccessed = pad;
        emit in->setPadStatus(pad, event == Event::NOTEON);
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
