
#include <iostream>
#include <stdio.h>

#include "device.hpp"
#include "utils.h"

using namespace std;

Device::Device(snd_ctl_t *ctl, int devId):
    handle(ctl), deviceId(devId), deviceCode({0}),
    padReceiver(&Device::defaultPadReceiver),
    sliderReceiver(&Device::defaultSliderReceiver)
{
    snprintf(deviceCode, DEVICECODE_SIZE, "hw:%d", deviceId);
}

Device::Device(snd_seq_client_info_t *cinfo, snd_seq_port_info_t *pinfo):
    client(cinfo), port(pinfo),
    padReceiver(&Device::defaultPadReceiver),
    sliderReceiver(&Device::defaultSliderReceiver)
{
    clientId = snd_seq_port_info_get_client(pinfo);
    portId = snd_seq_port_info_get_port(pinfo);
    name = snd_seq_client_info_get_name(cinfo);
    deviceId = snd_seq_port_info_get_client(pinfo);

    snprintf(deviceCode, DEVICECODE_SIZE, "%d:%d", deviceId, snd_seq_port_info_get_port(pinfo));
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

    ///@todo understand why
    /* we need both READ and SUBS_READ */
    if ((snd_seq_port_info_get_capability(port)
         & (SND_SEQ_PORT_CAP_READ | SND_SEQ_PORT_CAP_SUBS_READ))
        != (SND_SEQ_PORT_CAP_READ | SND_SEQ_PORT_CAP_SUBS_READ))
        return false;

    return true;
}

void Device::print() const
{
    cout << "Device n° " << deviceId << " (" << deviceCode << ")" << endl;
}

void Device::processEvent(snd_seq_event_t *event)
{
    if(event->source.client != clientId || event->source.port != portId){
        D("Not for me.");
    }


    switch(event->type){
    case SND_SEQ_EVENT_NOTE:
        D("SND_SEQ_EVENT_NOTE");
        break;
    case SND_SEQ_EVENT_NOTEON:
        padReceiver(event->data.note.note, Event::NOTEON, event->data.note.velocity);
//        D("SND_SEQ_EVENT_NOTEON [%d, %d, %d, %d, %d]", event->data.note.channel,
//          event->data.note.duration, event->data.note.note,
//          event->data.note.off_velocity, event->data.note.velocity);
        break;
    case SND_SEQ_EVENT_NOTEOFF:
        padReceiver(event->data.note.note, Event::NOTEOFF, 0);

//        D("SND_SEQ_EVENT_NOTEOFF [%d, %d, %d, %d, %d]", event->data.note.channel,
//          event->data.note.duration, event->data.note.note,
//          event->data.note.off_velocity, event->data.note.velocity);
        break;
    case SND_SEQ_EVENT_KEYPRESS:
        D("SND_SEQ_EVENT_KEYPRESS");
        break;

    case SND_SEQ_EVENT_CONTROLLER:
//        D("SND_SEQ_EVENT_CONTROLLER");
        sliderReceiver(event->data.control.param, event->data.control.value);
        break;
    case SND_SEQ_EVENT_PGMCHANGE:
        D("SND_SEQ_EVENT_PGMCHANGE");
        break;
    case SND_SEQ_EVENT_CHANPRESS:
        padReceiver(event->data.control.channel, Event::VALUECHANGE, event->data.control.value);
//        D("SND_SEQ_EVENT_CHANPRESS [%d %d %d]", event->data.control.channel, event->data.control.param, event->data.control.value);
        break;
    case SND_SEQ_EVENT_PITCHBEND:
        D("SND_SEQ_EVENT_PITCHBEND");
        break;

    default:
        D(">> another event: %d", (int) event->type);
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
