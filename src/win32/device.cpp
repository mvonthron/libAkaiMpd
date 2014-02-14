
#include <iostream>
#include <stdio.h>

#include "device.hpp"
#include "utils.h"

using namespace std;

Device::Device()
{
    //~ snprintf(deviceCode, DEVICECODE_SIZE, "hw:%d", deviceId);
}


Device::~Device()
{
    D("Deleting %s (%d)", name.c_str(), deviceId);
}

void Device::init()
{
}

bool Device::isValid() const
{
    /* no name: must be an error */
    if(name.empty())
        return false;

    /* client = 0 => system stuff */
    if(deviceId <= 0)
        return false;

    if(name.find("Akai") == string::npos)
        return false;

    return true;
}

void Device::print() const
{
    cout << "Device n° " << deviceId << " (" << deviceCode << ")" << endl;
}

void Device::processEvent()
{
}

void Device::setPadReceiver(Device::PadReceiver receiver)
{
    if(receiver){
        padReceiver = receiver;
    }
}

void Device::setSliderReceiver(Device::SliderReceiver receiver)
{
    if(receiver){
        sliderReceiver = receiver;
    }
}

void Device::defaultPadReceiver(int id, Event::Type ev, int val)
{
    cout << ".. Pad " << id << ", Event: " << Event::toString(ev) <<  ", Value: " << val << endl;
}

void Device::defaultSliderReceiver(int id, int val)
{
    cout << ".. Slider " << id << ", Value: " << val << endl;
}



string Event::toString(Event::Type e)
{
    switch(e){
    case Event::NOTEON:
        return "Note On";
    case Event::NOTEOFF:
        return "Note Off";
    case Event::VALUECHANGE:
        return "Value Change";
    }
}
