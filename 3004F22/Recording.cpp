#include "Recording.h"

Recording::Recording(DeviceMediator* device, const string& name, int intensity, int group, int betteryPercent):
    name(name), intensity(intensity), group(group), batteryPercent(batteryPercent), Widget(device) {}

Recording::~Recording() { delete this; }

string Recording::getName() { return this->name; }

int Recording::getIntensity() { return this->intensity; }

int Recording::getGroup() { return this->group; }

int Recording::getBatteryPercent() { return this->batteryPercent; }
