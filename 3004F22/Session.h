#ifndef SESSION_H
#define SESSION_H

#include "Widget.h"

using namespace std;

class Session : public Widget {
    public:
        Session(DeviceMediator* device);
        ~Session();
};

#endif // SESSION_H
