#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <alsa/asoundlib.h>

#define DEVICECODE_SIZE 32

class Device
{
    typedef void (*eventProcessor)(snd_seq_event_t *);

public:
    Device(snd_ctl_t *ctl, int devId);
    Device(snd_seq_client_info_t *cinfo, snd_seq_port_info_t *pinfo);
    virtual ~Device();

    virtual void init();
    virtual bool isValid();
    virtual void print();

    virtual void processEvent(snd_seq_event_t *event);

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
