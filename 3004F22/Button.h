#ifndef BUTTON_H
#define BUTTON_H

#include "Widget.h"

using namespace std;

class Button : public Widget {
    public:
        Button(DeviceMediator* device);
        ~Button();
};

#endif // BUTTON_H
