#include "Light.h"

Light::Light(DeviceMediator* device, const string& name): lightName(name), isOn(false), Widget(device){}

Light::~Light(){
    delete this;
}
