#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <alsa/asoundlib.h>

#define DEVICECODE_SIZE 32

struct Event {
    enum Type {
        NOTEON,
        NOTEOFF,
        VALUECHANGE
    };
    static std::string toString(Event::Type e);
};


class Device
{
    typedef void (*eventProcessor)(snd_seq_event_t *);
    typedef void (*PadReceiver)(int, Event::Type, int);
    typedef void (*SliderReceiver)(int, int);

public:
    Device(snd_ctl_t *ctl, int devId);
    Device(snd_seq_client_info_t *cinfo, snd_seq_port_info_t *pinfo);
    virtual ~Device();

    virtual void init();
    virtual bool isValid();
    virtual void print();

    virtual void processEvent(snd_seq_event_t *event);
    void setPadReceiver(PadReceiver receiver);
    void setSliderReceiver(SliderReceiver receiver);

    int clientId;
    int portId;

private:
    PadReceiver padReceiver;
    SliderReceiver sliderReceiver;

    static void defaultPadReceiver(int id, Event::Type ev, int val);
    static void defaultSliderReceiver(int id, int val);

    snd_ctl_t *handle;  ///@todo remove?
    snd_rawmidi_info_t *info;   ///@todo remove?

    snd_seq_client_info_t *client;
    snd_seq_port_info_t *port;

    std::string name;
    char deviceCode[DEVICECODE_SIZE];
    int deviceId;
};

#endif // DEVICE_H
