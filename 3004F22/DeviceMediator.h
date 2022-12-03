#ifndef DEVICEMEDIATOR_H
#define DEVICEMEDIATOR_H

#include <iostream>
#include <string>

using namespace std;

class Widget;
class DeviceMediator {
    public:
        virtual ~DeviceMediator(){}
        virtual void WidgetChanged(Widget*, const string& widgetName)=0;

    protected:
        DeviceMediator(){}
        // virtual void createWidgets() = 0;
};

#endif // DEVICEMEDIATOR_H
