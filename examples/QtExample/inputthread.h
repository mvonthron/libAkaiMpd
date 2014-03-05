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
    
signals:
    
public slots:
    
protected:
    virtual void run();

private:
    DeviceManager devManager;
};

#endif // INPUTTHREAD_H
