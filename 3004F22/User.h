#ifndef USER_H
#define USER_H

#include "Widget.h"

using namespace std;

class User : public Widget {
    public:
        User(DeviceMediator* device, const string& name, int intensity);
        ~User();

    private:
        string name;
        int intensity;
};

#endif // USER_H
