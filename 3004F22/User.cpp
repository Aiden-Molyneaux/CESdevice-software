#include "User.h"

User::User(DeviceMediator *device, const string &name, int intensity): name(name), intensity(intensity), Widget(device) {}

User::~User() { delete this;}
