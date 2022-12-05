#ifndef GROUP_H
#define GROUP_H

#include "Widget.h"

using namespace std;

class Group : public Widget {
    public:
        Group(DeviceMediator* device, const string& name, int lengthMS);
        ~Group();

        int getLengthMS();

    private:
        string groupName;
        int lengthMS;
};

#endif // GROUP_H
