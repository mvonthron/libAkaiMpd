
#include <iostream>
#include <stdio.h>

#include "device.h"
#include "utils.h"

using namespace std;

Device::Device(snd_ctl_t *ctl, int devId):
    handle(ctl), deviceId(devId), deviceCode({0})
{
    snprintf(deviceCode, DEVICECODE_SIZE, "hw:%d", deviceId);
    D("Creating device %d", deviceId);
}

Device::Device(snd_seq_client_info_t *cinfo, snd_seq_port_info_t *pinfo):
    client(cinfo), port(pinfo)
{
//    printf("%3d:%-3d  %-32.32s %s\n",
//           snd_seq_port_info_get_client(port),
//           snd_seq_port_info_get_port(port),
//           snd_seq_client_info_get_name(client),
//           snd_seq_port_info_get_name(port));
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
#if 0
    snd_rawmidi_info_t *info;
    const char *_name;
    const char *sub_name;
    int subs, subs_in, subs_out;
    int sub;
    int err;

    snd_rawmidi_info_alloca(&info);
    snd_rawmidi_info_set_device(info, deviceId);

    snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_INPUT);
    err = snd_ctl_rawmidi_info(handle, info);
    if (err >= 0)
        subs_in = snd_rawmidi_info_get_subdevices_count(info);
    else
        subs_in = 0;

    snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_OUTPUT);
    err = snd_ctl_rawmidi_info(handle, info);
    if (err >= 0)
        subs_out = snd_rawmidi_info_get_subdevices_count(info);
    else
        subs_out = 0;

    subs = subs_in > subs_out ? subs_in : subs_out;
    if (!subs)
        return;

    for (sub = 0; sub < subs; ++sub) {
        snd_rawmidi_info_set_stream(info, sub < subs_in ?
                        SND_RAWMIDI_STREAM_INPUT :
                        SND_RAWMIDI_STREAM_OUTPUT);
        snd_rawmidi_info_set_subdevice(info, sub);
        err = snd_ctl_rawmidi_info(handle, info);
        if (err < 0) {
            D("cannot get rawmidi information %d:%d:%d: %s\n",
                  0, deviceId, sub, snd_strerror(err));
            return;
        }
        name = _name = snd_rawmidi_info_get_name(info);
        sub_name = snd_rawmidi_info_get_subdevice_name(info);
        if (sub == 0 && sub_name[0] == '\0') {
            printf("%c%c  hw:%d,%d    %s",
                   sub < subs_in ? 'I' : ' ',
                   sub < subs_out ? 'O' : ' ',
                   0, deviceId, _name);
            if (subs > 1)
                printf(" (%d subdevices)", subs);
            putchar('\n');
            break;
        } else {
            printf("%c%c  hw:%d,%d,%d  %s\n",
                   sub < subs_in ? 'I' : ' ',
                   sub < subs_out ? 'O' : ' ',
                   0, deviceId, sub, sub_name);
        }
    }
#endif
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

