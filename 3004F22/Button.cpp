#include "Button.h"

Button::Button(DeviceMediator* device, const string& name): buttonName(name), Widget(device) {

}

Button::~Button() {
    delete this;
}

void Button::pressed(){
    changed(this->buttonName);
}




