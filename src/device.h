#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <alsa/asoundlib.h>

#define DEVICECODE_SIZE 32

class Device
{
public:
    Device(snd_ctl_t *ctl, int devId);
    ~Device();

    void init();
    bool isValid();
    void print();

private:
    snd_ctl_t *handle;
    snd_rawmidi_info_t *info;

    std::string name;
    char deviceCode[DEVICECODE_SIZE];
    int deviceId;
};

#endif // DEVICE_H
