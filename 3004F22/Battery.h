#ifndef BATTERY_H
#define BATTERY_H

#include "Widget.h"

using namespace std;

class Battery : public Widget{
    public:
        Battery(DeviceMediator* device);
        ~Battery();

        double getBatteryLevel();
        void setBatteryLevel(double newBatteryLevel);
        void setBlinkFlag(bool flag);
        bool getBlinkFlag();
    private:
        double batteryLevel;
        bool blinkFlag = false;
};

#endif // BATTERY_H
