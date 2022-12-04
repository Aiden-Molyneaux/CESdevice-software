#ifndef LIGHT_H
#define LIGHT_H

#include "Widget.h"

using namespace std;

class Light : public Widget {
    public:
        Light(DeviceMediator* device, const string& name);
        ~Light();

    private:
        string lightName;
        bool isOn;
};

#endif // LIGHT_H
