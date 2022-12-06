#include "Recording.h"

Recording::Recording(DeviceMediator* device, const string& name, int intensity, int group, int batteryPercent, int connection):
    name(name), intensity(intensity), group(group), batteryPercent(batteryPercent), connection(connection), Widget(device) {}

Recording::~Recording() { delete this; }

string Recording::getName() { return this->name; }

int Recording::getIntensity() { return this->intensity; }

int Recording::getGroup() { return this->group; }

int Recording::getBatteryPercent() { return this->batteryPercent; }

int Recording::getConnection() { return this->connection; }
