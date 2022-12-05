#ifndef RECORDING_H
#define RECORDING_H

#include "Widget.h"

using namespace std;

class Recording : public Widget {
    public:
        Recording(DeviceMediator *device, const string& name, int intensity, int group, int batteryPercent);
        ~Recording();

        string getName();
        int getIntensity();
        int getGroup();
        int getBatteryPercent();

    private:
        string name;
        int intensity;
        int batteryPercent;
        int group;
};

#endif // RECORDING_H
