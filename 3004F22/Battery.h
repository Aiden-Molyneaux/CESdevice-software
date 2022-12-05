#ifndef BATTERY_H
#define BATTERY_H

#include "Widget.h"

using namespace std;

class Battery : public Widget{
    public:
        Battery(DeviceMediator* device);
        ~Battery();

        int getBatteryLevel();
        void setBatteryLevel(int newBatteryLevel);
        void setBlinkFlag(bool flag);
        bool getBlinkFlag();
    private:
        int batteryLevel;
        bool blinkFlag = false;
};

#endif // BATTERY_H
