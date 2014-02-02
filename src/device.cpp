
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

Device::~Device()
{
    D("Deleting %s (%d)", name.c_str(), deviceId);
}

void Device::init()
{
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
}

bool Device::isValid()
{
    return true;
}

void Device::print()
{
    cout << "Device n° " << deviceId << " (" << deviceCode << ")" << endl;
}

