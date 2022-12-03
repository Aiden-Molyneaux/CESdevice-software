#ifndef WIDGET_H
#define WIDGET_H

#include "DeviceMediator.h"

using namespace std;

class Widget {
    public:
        Widget(DeviceMediator* device);

        virtual void changed();
    private:
        DeviceMediator* device;
};

#endif // WIDGET_H
