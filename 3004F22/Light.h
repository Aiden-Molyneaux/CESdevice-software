#ifndef LIGHT_H
#define LIGHT_H

#include "Widget.h"

using namespace std;

class Light : public Widget {
    public:
        Light(DeviceMediator* device, const string& name);
        ~Light();

        bool getIsLightOn();
        void setIsLightOn(bool status);

    private:
        string lightName;
        bool isLightOn;
};

#endif // LIGHT_H
