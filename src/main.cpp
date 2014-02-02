#include <iostream>
#include <vector>

#include "devicelist.h"
#include "device.h"


using namespace std;


int main()
{
    DeviceList devList;
    devList.scanDevices();

    for(auto &dev: devList){
        dev->print();
    }

    return 0;
}

