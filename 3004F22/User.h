#ifndef USER_H
#define USER_H

#include "Widget.h"

using namespace std;

class User : public Widget {
    public:
        User(DeviceMediator* device, const string& name, int duration);
        ~User();

        int getDuration();
        string getName();

    private:
        string name;
        int duration;
};

#endif // USER_H
