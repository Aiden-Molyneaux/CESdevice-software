#ifndef RECORDING_H
#define RECORDING_H

#include "Widget.h"

using namespace std;

class Recording : public Widget {
    public:
        Recording(DeviceMediator *device, const string& name, int intensity, int initialIntensity, int group, double batteryPercent, int connection);
        ~Recording();

        string getName();
        int getIntensity();
        int getInitialIntensity();
        int getGroup();
        double getBatteryPercent();
        int getConnection();

    private:
        string name;
        int intensity;
        int initialIntensity;
        double batteryPercent;
        int group;
        int connection;
};

#endif // RECORDING_H
