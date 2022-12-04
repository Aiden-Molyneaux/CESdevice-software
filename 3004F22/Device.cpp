#include "Device.h"

Device::Device(const string& name): deviceName(name) {
    // Buttons initialization
    powerButton = new Button(this, "powerButton");
    upArrowButton = new Button(this, "upArrowButton");
    downArrowButton = new Button(this, "downArrowButton");
    selectButton = new Button(this, "selectButton");

    // Lights initialization
    powerLight = new Light(this, "powerLight");

    // Group and Sessions initialization
    groupTypes[0] = new Group(this, "20min");
    groupTypes[1] = new Group(this, "45min");
    groupTypes[2] = new Group(this, "userDesignated");

    for(int i=0; i<3; i++){}
}

Device::~Device(){}

// Widget change handler function
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

// GETTERS AND SETTERS
Button* Device::getPowerButton(){ return this->powerButton; }

Light* Device::getPowerLight(){ return this->powerLight; }
