#ifndef BUTTON_H
#define BUTTON_H

#include "Widget.h"

using namespace std;

class Button : public Widget {
    public:
        Button(DeviceMediator* device, const string& name);
        ~Button();

        void pressed();

    private:
        string buttonName;
};

#endif // BUTTON_H
