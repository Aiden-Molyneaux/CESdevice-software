#ifndef DEVICE_H
#define DEVICE_H

#include "Button.h"
#include "Light.h"
#include "Battery.h"
#include "Group.h"
#include "Session.h"
#include "User.h"
#include "Recording.h"

#include <iostream>
#include <string>

using namespace std;

class Device : public DeviceMediator {
    public:
        Device(const string& name);
        virtual ~Device();

        virtual void WidgetChanged(Widget*, const string& widgetName);

        void powerOn();
        void setSoftPower(bool value);
        void powerOff();
        int addUser(const string& name, int intensity);
        int addRecording(const string& name, int intensity, int group, int batteryPercent, int connection);
        int getNumRecordings();
        Recording* getRecordingAt(int index);
        User* getUserByName(const string& name);

        Battery* getBattery();
        Button* getPowerButton();
        Button* getUpArrowButton();
        Button* getDownArrowButton();

        Light* getPowerLight();

        Group* getGroups(int groupNum);
        Session* getSessions(int groupNum, int sessionNum);

        bool getIsPoweredOn();
        bool getIsSoftPoweredOn();
        bool getIsInSession();
        void setIsInSession(bool status);
        bool getFirstBoot();
        void setFirstBoot(bool value);
        bool getTimeout();
        void setTimeout(bool value);

        int getCurrentIntensity();
        void setCurrentIntensity(int intensity);

    private:
        string deviceName;

        Battery* battery;
        Button* powerButton;
        Button* upArrowButton;
        Button* downArrowButton;
        Button* selectButton;

        Light* powerLight;

        Group* groupTypes[3];
        Session* sessionTypes[3][4];
        User* users[5];
        Recording* recordings[100];

        int currentIntensity;
        int numUsers = 0;
        int numRecordings = 0;

        bool isPowered;
        bool isSoftPowered;
        bool inSession;
        bool firstBoot = true;
        bool timeout = false;
};

#endif // DEVICE_H
