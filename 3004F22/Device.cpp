#include "Device.h"

Device::Device(const string& name): deviceName(name), isPowered(false), inSession(false), currentIntensity(0) {
    // Battery initialization
    battery = new Battery(this);

    // Button initialization
    powerButton = new Button(this, "powerButton");

    // Light initialization
    powerLight = new Light(this, "powerLight");

    // Groups and Sessions initialization
    groupTypes[0] = new Group(this, "20min", 4000);
    groupTypes[1] = new Group(this, "45min", 8500);
    groupTypes[2] = new Group(this, "userDesignated", 0);

    for(int i=0; i<3; i++){
        sessionTypes[i][0] = new Session(this, "delta", 5);
        sessionTypes[i][1] = new Session(this, "theta", 8);
        sessionTypes[i][2] = new Session(this, "alpha", 11);
        sessionTypes[i][3] = new Session(this, "beta", 15);
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
    }
}

void Device::powerOn(){
    if(battery->getBatteryLevel()<33){
        return;
    }
    isPowered = true;
    powerLight->setIsLightOn(true);
}

void Device::setSoftPower(bool value){
    isSoftPowered = value;
}

void Device::powerOff(){
    powerLight->setIsLightOn(false);
    isPowered = false;
}

int Device::addUser(const string& name, int duration) {
    if (numUsers == 5) { return -1; }

    users[numUsers] = new User(this, name, duration);
    numUsers++;
    return numUsers;
}

int Device::addRecording(const string& name, int intensity, int initialIntensity, int group, int batteryPercent, int connection) {
    if (numRecordings == 100) { return -1; }

    recordings[numRecordings] = new Recording(this, name, intensity, initialIntensity, group, batteryPercent, connection);
    numRecordings++;
    return numRecordings;
}

// GETTERS AND SETTERS
Battery* Device::getBattery(){ return this->battery; }

Button* Device::getPowerButton(){ return this->powerButton; }

Button* Device::getUpArrowButton(){ return this->upArrowButton; }

Button* Device::getDownArrowButton(){ return this->downArrowButton; }

Light* Device::getPowerLight(){ return this->powerLight; }

Group* Device::getGroups(int groupNum){ return this->groupTypes[groupNum]; }

Session* Device::getSessions(int groupNum, int sessionNum){ return this->sessionTypes[groupNum][sessionNum]; }

bool Device::getIsPoweredOn(){ return this->isPowered; }

bool Device::getIsSoftPoweredOn(){ return this->isSoftPowered; }

bool Device::getIsInSession(){ return this->inSession; }

void Device::setIsInSession(bool status){ this->inSession = status; }

int Device::getCurrentIntensity(){ return this->currentIntensity; }

void Device::setCurrentIntensity(int intensity){ this->currentIntensity = intensity; }

Recording* Device::getRecordingAt(int index) { return this->recordings[index]; }

int Device::getNumRecordings() { return this->numRecordings; }

User* Device::getUserByName(const string& name) {
    for (int i = 0; i < numUsers; i++) {
        if (users[i]->getName() == name) {
            return users[i];
        }
    }
    return NULL;
}

void Device::setFirstBoot(bool value) { this->firstBoot = value; }

bool Device::getFirstBoot() { return this->firstBoot; }

void Device::setTimeout(bool value) { this->timeout = value; }

bool Device::getTimeout() { return this->timeout; }

void Device::setRecordingFlag(bool value) { this->recordingFlag = value; }

bool Device::getRecordingFlag() { return this->recordingFlag; }
