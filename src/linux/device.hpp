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
    friend class DeviceManager;
    typedef void (*eventProcessor)(snd_seq_event_t *);
    typedef void (*PadReceiver)(int, Event::Type, int, void*);
    typedef void (*SliderReceiver)(int, int, void *);

public:
    Device(snd_ctl_t *ctl, int devId);
    Device(snd_seq_client_info_t *cinfo, snd_seq_port_info_t *pinfo);
    virtual ~Device();

    virtual void init();
    virtual bool isValid() const;
    virtual void print() const;

    virtual void processEvent(snd_seq_event_t *event);
    void setPadReceiver(PadReceiver receiver, void *object=NULL);
    void setSliderReceiver(SliderReceiver receiver, void *object=NULL);

    int clientId;
    int portId;

private:
    PadReceiver padReceiver;
    SliderReceiver sliderReceiver;

    static void defaultPadReceiver(int id, Event::Type ev, int val, void *obj=NULL);
    static void defaultSliderReceiver(int id, int val, void *obj=NULL);

    snd_ctl_t *handle;  ///@todo remove?
    snd_rawmidi_info_t *info;   ///@todo remove?

    snd_seq_client_info_t *client;
    snd_seq_port_info_t *port;

    std::string name;
    char deviceCode[DEVICECODE_SIZE];
    int deviceId;
    void *callbackObject;
};

#endif // DEVICE_H
