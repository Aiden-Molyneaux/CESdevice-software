#include "Light.h"

Light::Light(DeviceMediator* device, const string& name): lightName(name), isLightOn(false), Widget(device){}

Light::~Light(){ delete this; }

bool Light::getIsLightOn(){ return this->isLightOn; }

void Light::setIsLightOn(bool status){ this->isLightOn= status; }
