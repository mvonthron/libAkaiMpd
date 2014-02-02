#include "devicelist.h"
#include "utils.h"

DeviceList::DeviceList()
{
}

DeviceList::~DeviceList()
{
    for(auto &e: list){
        delete e;
    }
    list.clear();
}

int DeviceList::scanDevicesForCard(int cardno)
{
    snd_ctl_t *ctl;
    char name[32];
    int err=0, count=0, device=-1;

    sprintf(name, "hw:%d", cardno);
    if ((err = snd_ctl_open(&ctl, name, 0)) < 0) {
        D("cannot open control for card %d: %s", cardno, snd_strerror(err));
        return -1;
    }

    for (;;) {
        if ((err = snd_ctl_rawmidi_next_device(ctl, &device)) < 0) {
            D("cannot determine device number: %s", snd_strerror(err));
            break;
        }
        if(device >= 0){
            D("Found device %d on card %d", device, cardno);
            Device *d = new Device(ctl, device);
            d->init();

            if( d->isValid() ) {
                list.push_back( d );
            }
            count++;
            //        list_device(ctl, cardno, device);
        }else{
            break;
        }
    }
    snd_ctl_close(ctl);
    return count;
}

void DeviceList::scanDevices()
{
    int cardno=-1, err=0;

    err = snd_card_next(&cardno);
    if(err < 0){
        D("Failed to scan cards (%s).", snd_strerror(err));
        return;
    }

    if(cardno < 0 ){
        D("No card found.");
        return;
    }

    do {
        D(">>> about to scan %d", cardno);
        int nb = scanDevicesForCard(cardno);
        D(">>> done with %d (found %d)", cardno, nb);

        if ((err = snd_card_next(&cardno)) < 0) {
            D("cannot determine card number: %s", snd_strerror(err));
            break;
        }

    } while (cardno >= 0);


    D("Device list contain %d elements.", (int) list.size());
}
