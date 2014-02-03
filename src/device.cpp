
#include <iostream>
#include <stdio.h>

#include "device.h"
#include "utils.h"

using namespace std;

Device::Device(snd_ctl_t *ctl, int devId):
    handle(ctl), deviceId(devId), deviceCode({0})
{
    snprintf(deviceCode, DEVICECODE_SIZE, "hw:%d", deviceId);
}

Device::Device(snd_seq_client_info_t *cinfo, snd_seq_port_info_t *pinfo):
    client(cinfo), port(pinfo)
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

bool Device::isValid()
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

void Device::print()
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
        D("SND_SEQ_EVENT_NOTEON");
        break;
    case SND_SEQ_EVENT_NOTEOFF:
        D("SND_SEQ_EVENT_NOTEOFF");
        break;
    case SND_SEQ_EVENT_KEYPRESS:
        D("SND_SEQ_EVENT_KEYPRESS");
        break;

    case SND_SEQ_EVENT_CONTROLLER:
        D("SND_SEQ_EVENT_CONTROLLER");
        break;
    case SND_SEQ_EVENT_PGMCHANGE:
        D("SND_SEQ_EVENT_PGMCHANGE");
        break;
    case SND_SEQ_EVENT_CHANPRESS:
        D("SND_SEQ_EVENT_CHANPRESS");
        break;
    case SND_SEQ_EVENT_PITCHBEND:
        D("SND_SEQ_EVENT_PITCHBEND");
        break;

    default:
        D(">> another event: %d", (int) event->type);
    }
}

