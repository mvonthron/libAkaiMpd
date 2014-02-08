#include <iostream>
#include <vector>

#include "devicemanager.hpp"
#include "device.hpp"

using namespace std;

void padReceiver(int id, Event::Type event, int value)
{
    std::cout << "Pad " << id << " value: " << value << endl;
}

void sliderReceiver(int id, int value)
{
    std::cout << "Slider " << id << " value: " << value << endl;
}

int main()
{
    DeviceManager devManager;
    devManager.scanDevices();

    for(auto &dev: devManager){
        dev->setPadReceiver(&padReceiver);

        dev->print();
    }

    devManager.loop();

    return 0;
}

