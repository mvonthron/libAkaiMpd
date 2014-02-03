#include "devicemanager.h"
#include "utils.h"

DeviceManager::DeviceManager()
{
    init();
}

DeviceManager::~DeviceManager()
{
    snd_seq_close(handle);

    for(auto &e: list){
        delete e;
    }
    list.clear();
}

void DeviceManager::init()
{
    int err;

    /* open sequencer */
    err = snd_seq_open(&handle, "default", SND_SEQ_OPEN_DUPLEX, 0);
    if(err < 0){
        D("Failed opening sequencer");
        return;
    }

    /* set our client's name */
    err = snd_seq_set_client_name(handle, "libSeq");
    if(err < 0){
        D("Failed setting name");
        return;
    }

    err = snd_seq_create_simple_port(handle, "libSeq",
             SND_SEQ_PORT_CAP_WRITE |
             SND_SEQ_PORT_CAP_SUBS_WRITE,
             SND_SEQ_PORT_TYPE_MIDI_GENERIC |
             SND_SEQ_PORT_TYPE_APPLICATION);
    if(err < 0){
        D("Failed creating port");
        return;
    }

}


int DeviceManager::scanDevicesForCard(int cardno)
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

void DeviceManager::scanDevices()
{
    snd_seq_client_info_t *cinfo;
    snd_seq_port_info_t *pinfo;

    snd_seq_client_info_alloca(&cinfo);
    snd_seq_port_info_alloca(&pinfo);

    snd_seq_client_info_set_client(cinfo, -1);
    while (snd_seq_query_next_client(handle, cinfo) >= 0) {
        int client = snd_seq_client_info_get_client(cinfo);

        snd_seq_port_info_set_client(pinfo, client);
        snd_seq_port_info_set_port(pinfo, -1);

        while (snd_seq_query_next_port(handle, pinfo) >= 0) {
            Device *d = new Device(cinfo, pinfo);
            if(d->isValid()){
                snd_seq_connect_from(handle, 0, d->clientId, d->portId);
                list.push_back(d);
            }else{
                delete d;
            }
        }
    }

    D("Device list contain %d elements.", (int) list.size());

}

void DeviceManager::loop()
{
    struct pollfd *pfds;
    int npfds;
    int c, err;
    npfds = snd_seq_poll_descriptors_count(handle, POLLIN);
    D("npfds: %d", npfds);
    pfds = (struct pollfd *)alloca(sizeof(*pfds) * npfds);
    for (;;) {
        snd_seq_poll_descriptors(handle, pfds, npfds, POLLIN);
        if (poll(pfds, npfds, -1) < 0)
            break;
        do {
            snd_seq_event_t *event;
            err = snd_seq_event_input(handle, &event);
            if (err < 0)
                break;
            if (event){
                list[0]->processEvent(event);
//                dump_event(event);
            }
        } while (err > 0);
        fflush(stdout);
//        if (stop)
//            break;
    }

    snd_seq_close(handle);
}

