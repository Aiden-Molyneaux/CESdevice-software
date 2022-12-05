#include "Group.h"

Group::Group(DeviceMediator* device, const string& name, int lengthMS): groupName(name), lengthMS(lengthMS), Widget(device) {}

Group::~Group(){ delete this; }

int Group::getLengthMS(){ return this->lengthMS; }
