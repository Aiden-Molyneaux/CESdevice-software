#include "Light.h"

Light::Light(DeviceMediator* device, const string& name): lightName(name), Widget(device){}

Light::~Light(){
    delete this;
}
