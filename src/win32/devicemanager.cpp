#include <windows.h>
#include <mmsystem.h>

#include "devicemanager.hpp"
#include "utils.h"


DeviceManager::DeviceManager()
{
    init();
}

DeviceManager::~DeviceManager()
{
    for(std::vector<Device *>::iterator it = list.begin(); it != list.end(); it++){
        delete *it;
    }
    list.clear();
}

void DeviceManager::init()
{
}


void DeviceManager::scanDevices()
{
    int nbDev = midiInGetNumDevs();
    if(nbDev <= 0)
        return;

    MIDIINCAPS caps;
    int ret=-1;
    for(int i=0; i<nbDev; ++i){
        ret = midiInGetDevCaps(i, &caps, sizeof(caps));
        if(ret){
            D("Error");
            continue;
        }
		Device *d = new Device(std::string(caps.szPname), i);

		if(d->isValid()){
			list.push_back(d);
		}else{
			delete d;
		}
    }

    D("Device list contain %d elements.", (int) list.size());
}

void DeviceManager::loop()
{
	/* no need on Windows */
}

