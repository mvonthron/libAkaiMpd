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
    int nbDev = midiInGetNumDevs();
    D("Nb MIDI devices: %d", nbDev);

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

        printf(".. %S .. [%d, %d, %d]\n", caps.szPname, caps.wMid, caps.wPid, caps.vDriverVersion);
		if(d->isValid()){
			list.push_back(d);
		}else{
			D("Invalid.");
			delete d;
		}
    }

    //D("Device list contain %d elements.", (int) list.size());

}

void DeviceManager::loop()
{

}

