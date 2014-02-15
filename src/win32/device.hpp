#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <windows.h>
#include <mmsystem.h>

#define DEVICECODE_SIZE 32

struct Event {
    enum Type {
        NOTEON,
        NOTEOFF,
        VALUECHANGE
    };
    static std::string toString(Event::Type e);
};

struct Status {
	enum Type {
		CLOSED,
		INIT,
		OPENED,
		ERR /* thanks for the ERROR macro... */
	};
	static std::string toString(Status::Type e);
};

class __declspec(dllexport) Device
{
    typedef void (*PadReceiver)(int, Event::Type, int);
    typedef void (*SliderReceiver)(int, int);

public:
    Device(std::string _name, int _id);
    virtual ~Device();

    virtual void init();
    virtual bool isValid() const;
    virtual void print() const;

	void setStatus(Status::Type);
	void dispatch(DWORD_PTR msg, DWORD_PTR timestamp);

    static void CALLBACK processEvent(HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2);
    void setPadReceiver(PadReceiver receiver);
    void setSliderReceiver(SliderReceiver receiver);


private:
    PadReceiver padReceiver;
    SliderReceiver sliderReceiver;

    static void defaultPadReceiver(int id, Event::Type ev, int val);
    static void defaultSliderReceiver(int id, int val);

    std::string name;
    HMIDIIN handle;
    int deviceId;
	Status::Type status;
};

#endif // DEVICE_H
