#ifndef DEVICE_H
#define DEVICE_H

#include "Button.h"
#include "Group.h"
#include "Session.h"

#include <iostream>
#include <string>

using namespace std;

class Device : public DeviceMediator {
    public:
        Device(const string& name);
        virtual ~Device();

        virtual void WidgetChanged(Widget*);
    private:
        string deviceName;
};

#endif // DEVICE_H
