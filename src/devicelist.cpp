#include "devicelist.h"

DeviceList::DeviceList()
{
    list.push_back(new Device);
}

DeviceList::~DeviceList()
{
    for(auto &e: list){
        delete e;
    }
    list.clear();
}



const std::vector<Device *> &DeviceList::listDevices()
{
    return list;
}
