#ifndef DEVICEMEDIATOR_H
#define DEVICEMEDIATOR_H

#include <iostream>
#include <string>

class Widget;
class DeviceMediator {
    public:
    virtual ~DeviceMediator(){}
        virtual void WidgetChanged(Widget*)=0;

    protected:
        DeviceMediator(){}
        virtual void createWidgets() = 0;
};

#endif // DEVICEMEDIATOR_H
