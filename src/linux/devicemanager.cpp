#include "devicemanager.hpp"
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
            }
        } while (err > 0);
        fflush(stdout);
//        if (stop)
//            break;
    }

    snd_seq_close(handle);
}

