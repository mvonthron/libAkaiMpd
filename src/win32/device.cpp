
#include <iostream>
#include <stdio.h>

#include "device.hpp"
#include "utils.h"

using namespace std;

Device::Device(string _name, int _id): name(_name), deviceId(_id)
{
    //~ snprintf(deviceCode, DEVICECODE_SIZE, "hw:%d", deviceId);
	init();
	if(isValid()){
		midiInStart(handle);
	}
}


Device::~Device()
{
    D("Deleting %s (%d)", name.c_str(), deviceId);
}

void Device::init()
{
	int ret = midiInOpen(&handle, deviceId, (DWORD_PTR) Device::processEvent, (DWORD_PTR) this, CALLBACK_FUNCTION);

	if(ret){
		cout << "Could not open dev" << endl;
		deviceId = -1;
	}
}

bool Device::isValid() const
{
    /* no name: must be an error */
    if(name.empty())
        return false;

    /* client = 0 => system stuff */
    if(deviceId < 0)
        return false;

    if(name.find("Akai") == string::npos)
        return false;

    return true;
}

void Device::print() const
{
    cout << "Device " << name << endl;
}

void CALLBACK Device::processEvent(HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{

	switch(wMsg) {
	case MIM_OPEN:
		printf("Midi device opened\n");
		break;
	case MIM_CLOSE:
		printf("Midi device closed\n");
		break;
	case MIM_DATA:
		printf("Midi data\n");
		//handleData(dwParam1, dwParam1);
		break;
	case MIM_MOREDATA:
		printf("Some more data\n");
		break;
	case MIM_LONGDATA:
		printf("Some long data\n");
		break;
	case MIM_ERROR:
		printf("*** Error!\n");
		break;
	default:
		printf("Msg: %d\n", wMsg);
	}
}


void Device::setPadReceiver(Device::PadReceiver receiver)
{
    if(receiver){
        padReceiver = receiver;
    }
}

void Device::setSliderReceiver(Device::SliderReceiver receiver)
{
    if(receiver) {
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
    switch(e) {
    case Event::NOTEON:
        return "Note On";
    case Event::NOTEOFF:
        return "Note Off";
    case Event::VALUECHANGE:
        return "Value Change";
    }
}
