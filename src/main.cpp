#include <iostream>
#include <vector>

#include "devicemanager.h"
#include "device.h"

using namespace std;


int main()
{
    DeviceManager devManager;
    devManager.scanDevices();

    for(auto &dev: devManager){
        dev->print();
    }

    devManager.loop();

    return 0;
}

