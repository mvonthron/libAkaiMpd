#ifndef INPUTTHREAD_H
#define INPUTTHREAD_H

#include <QThread>

#include "devicemanager.hpp"
#include "device.hpp"


class InputThread : public QThread
{
    Q_OBJECT
public:
    explicit InputThread(QObject *parent = 0);
    const static int PAD_OFFSET=35;

    
signals:
    void setPadStatus(int, bool);
    void setPadValue(int, int);

    void setSlider(int);
    void log(QString);
    
public slots:
    static void padReceiver(int id, Event::Type event, int value, void *object);
    static void sliderReceiver(int id, int value, void *object);
    
protected:
    virtual void run();

private:

    DeviceManager devManager;
};

#endif // INPUTTHREAD_H
