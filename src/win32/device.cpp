
#include <iostream>
#include <stdio.h>

#include "device.hpp"
#include "utils.h"

using namespace std;

Device::Device(string _name, int _id): name(_name), deviceId(_id), status(Status::CLOSED)
{
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

    /* */
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
	Device *dev = (Device *) dwInstance;

	switch(wMsg) {
	case MIM_OPEN:
		cout << "Opening" << endl;
		dev->setStatus(Status::OPENED);
		break;
	case MIM_CLOSE:
		dev->setStatus(Status::CLOSED);
		break;
	case MIM_DATA:
		dev->dispatch(dwParam1, dwParam1);
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

void Device::setStatus(Status::Type st)
{
	status = st;
	cout << "Status set to " << Status::toString(status) << endl;
}

void Device::dispatch(DWORD_PTR msg, DWORD_PTR timestamp)
{
	cout << "Event" << endl;
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

string Status::toString(Status::Type s)
{
	switch(s){
	case Status::OPENED:
		return "Open";
	case Status::INIT:
		return "Init";
	case Status::CLOSED:
		return "Close";
	case Status::ERR:
		return "Error";
	}
}