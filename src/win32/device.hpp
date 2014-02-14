#ifndef DEVICE_H
#define DEVICE_H

#include <string>

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
    typedef void (*PadReceiver)(int, Event::Type, int);
    typedef void (*SliderReceiver)(int, int);

public:
    Device();
    virtual ~Device();

    virtual void init();
    virtual bool isValid() const;
    virtual void print() const;

    virtual void processEvent(/* */);
    void setPadReceiver(PadReceiver receiver);
    void setSliderReceiver(SliderReceiver receiver);

    int clientId;
    int portId;

private:
    PadReceiver padReceiver;
    SliderReceiver sliderReceiver;

    static void defaultPadReceiver(int id, Event::Type ev, int val);
    static void defaultSliderReceiver(int id, int val);

    std::string name;
    char deviceCode[DEVICECODE_SIZE];
    int deviceId;
};

#endif // DEVICE_H
