#include "Session.h"

Session::Session(DeviceMediator* device, const string& name, int intensity): sessionName(name), intensity(intensity), Widget(device) {}

Session::~Session(){ delete this; }

int Session::getIntensity(){
    return this->intensity;
}
