#ifndef SESSION_H
#define SESSION_H

#include "Widget.h"

using namespace std;

class Session : public Widget {
    public:
        Session(DeviceMediator* device, const string& name);
        ~Session();

    private:
        string sessionName;
};

#endif // SESSION_H
