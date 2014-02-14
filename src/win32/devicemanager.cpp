#include "devicemanager.hpp"
#include "utils.h"

DeviceManager::DeviceManager()
{
    init();
}

DeviceManager::~DeviceManager()
{

    for(auto &e: list){
        delete e;
    }
    list.clear();
}

void DeviceManager::init()
{
}


void DeviceManager::scanDevices()
{
    D("Device list contain %d elements.", (int) list.size());

}

void DeviceManager::loop()
{

}

