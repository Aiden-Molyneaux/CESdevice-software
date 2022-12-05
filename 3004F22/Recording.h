#ifndef RECORDING_H
#define RECORDING_H

#include "Widget.h"

using namespace std;

class Recording : public Widget {
    public:
        Recording(DeviceMediator *device, const string& name);
        ~Recording();

        string getName();

    private:
        string name;
};

#endif // RECORDING_H
