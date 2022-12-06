#include "Recording.h"

Recording::Recording(DeviceMediator* device, const string& name, int intensity, int initialIntensity, int group, double batteryPercent, int connection):
    name(name), intensity(intensity), initialIntensity(initialIntensity), group(group), batteryPercent(batteryPercent), connection(connection), Widget(device) {}

Recording::~Recording() { delete this; }

string Recording::getName() { return this->name; }

int Recording::getIntensity() { return this->intensity; }

int Recording::getInitialIntensity() { return this->initialIntensity; }

int Recording::getGroup() { return this->group; }

double Recording::getBatteryPercent() { return this->batteryPercent; }

int Recording::getConnection() { return this->connection; }
