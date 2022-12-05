#ifndef DEVICE_H
#define DEVICE_H

#include "Button.h"
#include "Light.h"
#include "Battery.h"
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

        void powerOn();
        void setSoftPower(bool value);
        void powerOff();

        Battery* getBattery();
        Button* getPowerButton();
        Button* getUpArrowButton();
        Button* getDownArrowButton();

        Light* getPowerLight();

        bool getIsPoweredOn();
        bool getIsSoftPoweredOn();
    private:
        string deviceName;

        Battery* battery;
        Button* powerButton;
        Button* upArrowButton;
        Button* downArrowButton;
        Button* selectButton;

        Light* powerLight;

        Group* groupTypes[3];
        Session* sessionTypes[3][4];

        int currentIntensity;

        bool isPowered;
        bool isSoftPowered;
        bool inSession;
};

#endif // DEVICE_H
