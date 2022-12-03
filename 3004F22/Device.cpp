#include "Device.h"

Device::Device(const string& name): deviceName(name) {
    // Buttons
    powerButton = new Button(this, "powerButton");

    powerLight = new Light(this, "powerLight");
}

Device::~Device(){}

void Device::WidgetChanged(Widget*, const string& widgetName){
    if(widgetName == "powerButton"){
        if(isPowered){
            isPowered=false;
        } else {
            isPowered = true;
        }
    }
    cout << "Power: " << isPowered << endl;
}

Button* Device::getPowerButton(){
    return this->powerButton;
}

Light* Device::getPowerLight(){
    return this->powerLight;
}
