#ifndef DEVICELIST_H
#define DEVICELIST_H

#include <vector>
#include <alsa/asoundlib.h>

#include "device.hpp"

class DeviceManager
{
public:
    typedef std::vector<Device *>::iterator iterator;

    DeviceManager();
    ~DeviceManager();

    void scanDevices();
    void loop();

    bool empty() const {return list.empty(); }
    iterator begin() { return list.begin(); }
    iterator end()  { return list.end(); }

    Device* getDeviceByName(std::string name);


private:
    void init();
    std::vector<Device *> list;

    snd_seq_t *handle;
    snd_seq_addr_t *ports;
};


#endif // DEVICELIST_H
