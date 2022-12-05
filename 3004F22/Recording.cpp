#include "Recording.h"

Recording::Recording(DeviceMediator *device, const string &name): name(name), Widget(device) {}

Recording::~Recording() { delete this; }

string Recording::getName() { return this->name; }
