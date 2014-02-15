#ifndef DEVICELIST_H
#define DEVICELIST_H

#include <vector>

#include "device.hpp"

class __declspec(dllexport) DeviceManager
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


private:
    void init();
    std::vector<Device *> list;
};


#endif // DEVICELIST_H
