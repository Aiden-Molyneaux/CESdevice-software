#include "Battery.h"

Battery::Battery(DeviceMediator* device): batteryLevel(100), Widget(device) {}

Battery::~Battery(){ delete this; }

int Battery::getBatteryLevel(){ return this->batteryLevel; }

void Battery::setBatteryLevel(int newBatteryLevel){ this->batteryLevel = newBatteryLevel; }

void Battery::setBlinkFlag(bool flag) { this->blinkFlag = flag; }

bool Battery::getBlinkFlag() { return this->blinkFlag; }
