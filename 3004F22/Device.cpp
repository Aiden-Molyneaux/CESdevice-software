#include "Device.h"

Device::Device(const string& name): deviceName(name), isPowered(false), inSession(false), currentIntensity(0) {
    battery = new Battery(this);

    // Buttons initialization
    powerButton = new Button(this, "powerButton");

    // Lights initialization
    powerLight = new Light(this, "powerLight");

    // Group and Sessions initialization
    groupTypes[0] = new Group(this, "20min");
    groupTypes[1] = new Group(this, "45min");
    groupTypes[2] = new Group(this, "userDesignated");

    for(int i=0; i<3; i++){
        sessionTypes[i][0] = new Session(this, "delta");
        sessionTypes[i][1] = new Session(this, "theta");
        sessionTypes[i][2] = new Session(this, "alpha");
        sessionTypes[i][3] = new Session(this, "beta");
    }
}

Device::~Device(){
    delete battery;
    delete powerButton;
    delete powerLight;

    for(int i=0; i<3; i++){
        delete groupTypes[i];
        for(int j=0; j<4; j++){
            delete sessionTypes[i][j];
        }
    }
}

// Widget change handler function
void Device::WidgetChanged(Widget*, const string& widgetName){
    if(widgetName == "powerButton"){
        isPowered ? powerOff() : powerOn();
        cout << "Power: " << isPowered << endl;
        cout << "powerLight: " << powerLight->getIsLightOn() << endl;
    }
    else if(widgetName == "upArrowButton"){
    }
}

void Device::powerOn(){
    if(battery->getBatteryLevel()<33){
        cout << "Battery level too low" << endl;
        return;
    }
    isPowered = true;
    powerLight->setIsLightOn(true);
}

void Device::setSoftPower(bool value){
    isSoftPowered = value;
}

void Device::powerOff(){
    // implement soft-off
    if(inSession){
        for(int i=0; i<10; i++){
            currentIntensity-=10;
            if(currentIntensity<=0){
                currentIntensity=0;
                break;
            }
        }
    }
    powerLight->setIsLightOn(false);
    isPowered = false;
}

int Device::addUser(const string& name, int intensity) {
    if (numUsers == 5) { return -1; }

    users[numUsers] = new User(this, name, intensity);
    numUsers++;
    return numUsers;
}

int Device::addRecording(const string& name) {
    if (numRecordings == 100) { return -1; }

    recordings[numRecordings] = new Recording(this, name);
    numRecordings++;
    return numRecordings;
}

// GETTERS AND SETTERS
Battery* Device::getBattery(){ return this->battery; }

Button* Device::getPowerButton(){ return this->powerButton; }

Button* Device::getUpArrowButton(){ return this->upArrowButton; }

Button* Device::getDownArrowButton(){ return this->downArrowButton; }

Light* Device::getPowerLight(){ return this->powerLight; }

bool Device::getIsPoweredOn(){ return this->isPowered; }

bool Device::getIsSoftPoweredOn(){ return this->isSoftPowered; }

Recording* Device::getRecordingAt(int index) { return this->recordings[index]; }

int Device::getNumRecordings() { return this->numRecordings; }
