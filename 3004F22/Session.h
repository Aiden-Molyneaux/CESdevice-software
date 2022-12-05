#ifndef SESSION_H
#define SESSION_H

#include "Widget.h"

using namespace std;

class Session : public Widget {
    public:
        Session(DeviceMediator* device, const string& name, int intensity);
        ~Session();

        int getIntensity();

    private:
        string sessionName;
        int intensity;
};

#endif // SESSION_H
