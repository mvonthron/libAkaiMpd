#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <alsa/asoundlib.h>

#define DEVICECODE_SIZE 32

class Device
{
public:
    Device(snd_ctl_t *ctl, int devId);
    Device(snd_seq_client_info_t *cinfo, snd_seq_port_info_t *pinfo);
    ~Device();

    void init();
    bool isValid();
    void print();

    int clientId;
    int portId;

private:
    snd_ctl_t *handle;  ///@todo remove?
    snd_rawmidi_info_t *info;   ///@todo remove?

    snd_seq_client_info_t *client;
    snd_seq_port_info_t *port;

    std::string name;
    char deviceCode[DEVICECODE_SIZE];
    int deviceId;
};

#endif // DEVICE_H
