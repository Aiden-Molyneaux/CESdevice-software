#include "Group.h"

Group::Group(DeviceMediator* device, const string& name): groupName(name), Widget(device) {}

Group::~Group(){ delete this; }
