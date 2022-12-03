#ifndef DEVICE_H
#define DEVICE_H

#include "Button.h"
#include "Light.h"
#include "Group.h"
#include "Session.h"

#include <iostream>
#include <string>

using namespace std;

class Device : public DeviceMediator {
    public:
        Device(const string& name);
        virtual ~Device();

        virtual void WidgetChanged(Widget*, const string& widgetName);

        Button* getPowerButton();
        Light* getPowerLight();
    private:
        string deviceName;
        Button* powerButton;

        Light* powerLight;

        bool isPowered;
};

#endif // DEVICE_H
