#include "User.h"

User::User(DeviceMediator *device, const string &name, int duration): name(name), duration(duration), Widget(device) {}

User::~User() { delete this;}

int User::getDuration() { return this->duration; }

string User::getName() { return this->name; }
