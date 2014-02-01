#include <iostream>
#include <vector>

#include "devicelist.h"
#include "device.h"

using namespace std;


int main()
{
    cout << "Hello World!" << endl;

    DeviceList devList;
    devList.listDevices();

    for(auto &dev: devList){
        cout << dev->test() << endl;
    }

    return 0;
}

