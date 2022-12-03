#ifndef GROUP_H
#define GROUP_H

#include "Widget.h"

using namespace std;

class Group : public Widget {
    public:
        Group(DeviceMediator* device);
        ~Group();
};

#endif // GROUP_H
