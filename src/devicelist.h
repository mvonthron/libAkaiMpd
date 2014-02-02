#ifndef DEVICELIST_H
#define DEVICELIST_H

#include <vector>
#include "device.h"

class DeviceList
{
public:
    typedef std::vector<Device *>::iterator iterator;

    DeviceList();
    ~DeviceList();

    void scanDevices();

    bool empty() const {return list.empty(); }
    iterator begin() { return list.begin(); }
    iterator end()  { return list.end(); }


private:
    std::vector<Device *> list;
    int scanDevicesForCard(int cardno);
};


#endif // DEVICELIST_H
