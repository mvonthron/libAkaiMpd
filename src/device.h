#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <alsa/asoundlib.h>


class Device
{
public:
    Device();
    std::string test() { return "test"; }

private:
    snd_ctl_t *handle;
    snd_rawmidi_info_t *info;

    std::string name;
};

#endif // DEVICE_H
