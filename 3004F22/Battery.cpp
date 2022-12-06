#include "Battery.h"

Battery::Battery(DeviceMediator* device): batteryLevel(100), Widget(device) {}

Battery::~Battery(){ delete this; }

double Battery::getBatteryLevel(){ return this->batteryLevel; }

void Battery::setBatteryLevel(double newBatteryLevel){ this->batteryLevel = newBatteryLevel; }

void Battery::setBlinkFlag(bool flag) { this->blinkFlag = flag; }

bool Battery::getBlinkFlag() { return this->blinkFlag; }
