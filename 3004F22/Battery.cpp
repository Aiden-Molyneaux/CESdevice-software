#include "Battery.h"

Battery::Battery(DeviceMediator* device): batteryLevel(50), Widget(device) {}

Battery::~Battery(){
    delete this;
}

int Battery::getBatteryLevel(){ return this->batteryLevel; }

void Battery::setBatteryLevel(int newBatteryLevel){ this->batteryLevel = newBatteryLevel; }
