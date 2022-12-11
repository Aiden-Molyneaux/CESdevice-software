#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    srand(time(0));

    // Initialize member variables
    selectedSession = 1;
    selectedGroup = 1;
    connectionIntensity = 1;
    timesIntensityAdjusted = 0;
    endSessionEarlyFlag = false;

    device = new Device("oasis pro");

    ui->batterySlider->setValue(device->getBattery()->getBatteryLevel()); // initiate batterySlider starting value

    connect(ui->powerButton, SIGNAL(pressed()), this, SLOT (pressPower()));
    connect(ui->powerButton, SIGNAL(released()), this, SLOT (powerReleased()));
    connect(ui->upArrowButton, SIGNAL(released()), this, SLOT (pressUpArrow()));
    connect(ui->downArrowButton, SIGNAL(released()), this, SLOT (pressDownArrow()));
    connect(ui->connectionSlider, SIGNAL(sliderReleased()), this, SLOT (changeConnectionSlider()));
    connect(ui->batterySlider, SIGNAL(sliderReleased()), this, SLOT (changeBatterySlider()));
    connect(ui->checkButton, SIGNAL(pressed()), this, SLOT (pressSelect()));
    connect(ui->checkButton, SIGNAL(released()), this, SLOT (releaseSelect()));
    connect(ui->connectEarclipsButton, SIGNAL(released()), this, SLOT (connectEarClips()));
    connect(ui->disconnectEarclipsButton, SIGNAL(released()), this, SLOT (disconnectEarClips()));
    connect(ui->addUserButton, SIGNAL(released()), this, SLOT (addUserButtonClicked()));
    connect(ui->printHistoryButton, SIGNAL(released()), this, SLOT (printHistoryButtonClicked()));
    connect(ui->playReplayButton, SIGNAL(released()), this, SLOT (playReplayButtonClicked()));
    connect(ui->stopButton, SIGNAL(released()), this, SLOT (stopPressed()));

    //TEST SLOTS
    connect(ui->testAddUser, SIGNAL(released()), this, SLOT (testAddUserClicked()));
    connect(ui->testAddBadUser, SIGNAL(released()), this, SLOT (testAddBadUserClicked()));
    connect(ui->testTherapy, SIGNAL(released()), this, SLOT (testTherapyClicked()));
    connect(ui->testRecordTherapy, SIGNAL(released()), this, SLOT (testRecordTherapyClicked()));
    connect(ui->testReplay, SIGNAL(released()), this, SLOT (testReplayClicked()));
    connect(ui->testOnlyRecord, SIGNAL(released()), this, SLOT (testOnlyRecordClicked()));
    connect(ui->testLostConnection, SIGNAL(released()), this, SLOT (testLostConnectionClicked()));
    connect(ui->testChangeIntensity, SIGNAL(released()), this, SLOT (testChangingIntensityClicked()));
    connect(ui->testDepleteBattery, SIGNAL(released()), this, SLOT (testDepleteBatteryClicked()));
}

MainWindow::~MainWindow() {
    delete ui;
    delete device; // make sure to delete our allocated device
}

// therapy() is the provides the main functionality of the device - initiating and performing therapy sessions
void MainWindow::therapy(int groupNum, int sessionNum, int recordingFlag, int overrideIntensity){
    string name = ui->nameComboBox->currentText().toStdString();
    int group = selectedGroup;
    int initialIntensity = device->getSessions(selectedGroup-1, selectedSession-1)->getIntensity();
    double batteryPercent = device->getBattery()->getBatteryLevel();

    //DO NOT ALLOW GROUP 3 TO BE USED WITH NO USER SPECIFIED
    if (group == 3 && ui->nameComboBox->currentText() == NULL) {
        ui->log->append("**CANNOT PERFORM THERAPY OF GROUP 3 - NO USER SPECIFIED**");
        return;
    }

    if (recordingFlag) {
        if (ui->nameComboBox->currentText() == NULL) {
            ui->log->append("CANNOT RECORD - NO USER SPECIFIED");
            recordingFlag = 0;
        } else {
            ui->log->append("**THIS SESSION WILL BE RECORDED UNDER USER " + QString::fromStdString(name) + "**");

            //CHECK IF USER WANTS TO JUST RECORD, OR DO SESSION AT THE SAME TIME
            changeBackgroundColor(ui->stopButton, "green", "stop", "20");
            sleepy(1);

            device->setRecordingFlag(false);
            pauseTimer.restart();
            pauseTimer.start();
            while (pauseTimer.elapsed() < 3000){
                sleepy(1);
                if (device->getRecordingFlag()) {
                    ui->log->append("**SESSION CANCELED**");
                    //DO RECORDING NOW - DEFAULT INTENSITY
                    addRecording(name, group, batteryPercent, initialIntensity);
                    changeBackgroundColor(ui->stopButton, "white", "stop", "20");
                    device->setRecordingFlag(false);
                    return;
                }
            }
        }
    }

    //SET STOP BUTTON BACK TO WHITE
    changeBackgroundColor(ui->stopButton, "white", "stop", "20");

    //TO BE USED FOR RECORDING
    int highestIntensity = initialIntensity;

    // Initial check to see if Battery needs to be replaced
    if(!checkBattery()){
        batteryWarning();
        device->setIsInSession(false);;
        return;
    }

    // Also check the connection strength
    if(connectionIntensity==1){
        ui->log->append("\nConnection level is poor. Please adjust.");
        return;
    }

    setTherapyLock(false); // lock all Connection, Intensity, and Power setting UI elements until Session begins

    device->setIsInSession(true);
    ui->log->append("Therapy session will begin in 5 seconds:\n");
    blinkSession(sessionNum); // make the session icon blink for a couple seconds

    // Begin session with blinking session icon and 5 second count down
    for(int i=5; i>0; i--){
        ui->log->moveCursor(QTextCursor::End);
        ui->log->insertPlainText(QString::number(i) + "... ");
        sleepy(500); // small sleep to simulate count down
    }

    int therapyLengthMS;
    // if groupNum == 3, then we need to get the user's designated session time length. Otherwise get the corresponding time length of the group chosen
    if(groupNum == 3){ therapyLengthMS = device->getUserByName(ui->nameComboBox->currentText().toStdString())->getDuration()*1000; } // *1000 because coverting seconds to milliseconds
    else{ therapyLengthMS = device->getGroups(groupNum-1)->getLengthMS(); }

    //SET CURRENT DEVICE INTENSITY ACCORDING TO OVERWRITEN VALUE - USED FOR RECORDING REPLAY
    if (overrideIntensity == -1) {
        device->setCurrentIntensity(device->getSessions(groupNum-1, sessionNum-1)->getIntensity());
    } else {
        device->setCurrentIntensity(overrideIntensity);
    }

    //GET DURATION IN MINUTES - USED FOR FOLLOWING log->append()
    int durationMinutes;
    switch (group) {
        case 1: durationMinutes = 20; break;
        case 2: durationMinutes = 45; break;
        case 3: durationMinutes = device->getUserByName(name)->getDuration(); break;
    }

    ui->log->append("Starting therapy session with:\n\tDuration: " + QString::number(durationMinutes) + "\n\tIntensity: " + QString::number(device->getCurrentIntensity()));

    updateIntensityLog(); // update Intensity log in UI

    setTherapyLock(true); // unlock all locked UI elements

    int remainingTime = 0; // only used if connection issues cause disconnect mid-session
    timesIntensityAdjusted = 0; // only used if intensity is adjusted during the session
    endSessionEarlyFlag = false; // only used if user decides to end session early by clicking the power button

    therapyTimer.start(); // Timer tracks elapsed time
    while(true){
        int flag = 0; // flag for if Session pauses due to Connection interruption

        // Check that Battery levels are sufficient - if not, end the session early
        if(!checkBattery()){
            batteryWarning();
            device->setIsInSession(false);
            return;
        }

        // When intensity is adjusted, about 750ms of therapy time is lost due to UI animation and processing
        // This check simply adds the lost time back onto the clock
        if(timesIntensityAdjusted){
            therapyLengthMS+=(750*timesIntensityAdjusted);
            timesIntensityAdjusted=0;

            if (device->getCurrentIntensity() > highestIntensity) { highestIntensity = device->getCurrentIntensity(); }
        }

        // Yet another check - this one is to catch if the user pressed the power button to end the session early
        if(endSessionEarlyFlag){
            endSessionEarly();
            break;
        }

        // During each loop (where the Device is not disconnected) record how long remains of the session
        if(connectionIntensity!=1){
            remainingTime = therapyLengthMS - therapyTimer.elapsed();
        }

        // This loop functions such that if the Device disconnects during a session, the device will wait until Connection returns and sets a flag to let the Device know it needs to resume a session
        while(connectionIntensity==1){
            flag = 1;
            ui->log->append("\nConnection level is poor. Please adjust."); // prompt user to reconnect
            sleepy(2000);
        }

        if(flag){ // flag is only true if session was disconnected due to connection issues - initiates return to session
            ui->log->append("\nResuming Session.");
            therapyTimer.restart(); // restart and begin timer again
            while(therapyTimer.elapsed() < remainingTime){ // execute the remaining time of the session
                // Battery level must be checked inside this loop as well
                if(!checkBattery()){
                    batteryWarning();
                    device->setIsInSession(false);
                    return;
                }
                if(timesIntensityAdjusted){
                    remainingTime+=(750*timesIntensityAdjusted);
                    timesIntensityAdjusted=0;
                }
                if(endSessionEarlyFlag){
                    endSessionEarly();
                    break;
                }
                drainBattery(device->getCurrentIntensity()); // deplete battery
                sleepy(150); // simulate real time
            }
            ui->log->append("Session Complete.\n"); // log to control that session has completed
            device->setIsInSession(false);

            //DO RECORDING HERE
            if (recordingFlag) {addRecording(name, group, batteryPercent, initialIntensity, highestIntensity);}

            break; // session ends, break therapy loop
        }

        // Remainder of this function executes if session does not disconnect (standard use case)
        drainBattery(device->getCurrentIntensity());

        sleepy(150);
        if(therapyTimer.elapsed() >= therapyLengthMS && connectionIntensity!=1){
            ui->log->append("Session Complete.\n");
            //DO RECORDING HERE
            if (recordingFlag) {addRecording(name, group, batteryPercent, initialIntensity, highestIntensity);}
            device->setIsInSession(false);
            break; // session ends, break therapy loop
        }
    }
}

// connectionTest function makes Connection UI elements flash to indicate Connection status
void MainWindow::connectionTest() {
    ui->graphLabel->setText("Currently indicating: Connection");
    ui->log->append("\nConnection lost. Please try again in a moment."); // report connection loss to control log

    setTherapyLock(false); // lock connection UI components for a moment

    // Blink 7 and 8 graph sections to indicate No Connection
    for(int i=10; i>0; i--){
        changeTextColor(ui->connectionTop, "red");
        sleepy(100);
        changeTextColor(ui->connectionTop, "gray");
        sleepy(100);
    }

    // gray out Connection graph
    changeTextColor(ui->connectionTop, "gray");
    changeTextColor(ui->connectionMiddle, "gray");
    changeTextColor(ui->connectionBottom, "gray");

    // animate red, yellow, green lights strobing up and down Connection graph
    for(int i=3; i>0; i--){
        changeTextColor(ui->connectionBottom, "gray");
        changeTextColor(ui->connectionTop, "red");
        sleepy(400);
        changeTextColor(ui->connectionTop, "gray");
        changeTextColor(ui->connectionMiddle, "yellow");
        sleepy(400);
        changeTextColor(ui->connectionMiddle, "gray");
        changeTextColor(ui->connectionBottom, "green");
        sleepy(400);
    }

    // gray out Connection graph, indicate "Please connect now", and allow connection
    changeTextColor(ui->connectionTop, "gray");
    changeTextColor(ui->connectionMiddle, "gray");
    changeTextColor(ui->connectionBottom, "gray");
    ui->log->append("\nPlease connect now.");
    setTherapyLock(true); // unlock the UI connection components
}

//REPLAY THE RECORDING SPECIFIED IN CONTROL WINDOW
void MainWindow::replayRecording(Recording *recording) {
    ui->log->append("\n**SETTING MACHINE STATE FOR REPLAY**");

    //GRAB PARAMETERS FROM RECORDING OBJECT
    int group = recording->getGroup();
    int intensity = recording->getIntensity();
    int initialIntensity = recording->getInitialIntensity();
    double batteryPercent = recording->getBatteryPercent();
    int connection = recording->getConnection();
    int session;

    //MAP INTENSITY TO SESSION
    switch (initialIntensity) {
        case 5: session = 1;
        break;
        case 8: session = 2;
        break;
        case 11: session = 3;
        break;
        case 15: session = 4;
        break;
    }

    //GET TO PROPER GROUP BUTTON
    while (group != selectedGroup) {
        cycleGroupButton();
        sleepy(200);
    }

    //GET TO PROPER SESSION BUTTON
    while (session != selectedSession) {
        pressUpArrow();
        sleepy(200);
    }

        //SET CONNECTION AND SLIDER
    connectionIntensity = connection;
    ui->connectionSlider->setValue(connectionIntensity);
    sleepy(200);

    //SET BATTERY AND SLIDER
    device->getBattery()->setBatteryLevel(batteryPercent);
    while (ui->batterySlider->value() != ceil(batteryPercent)) {
        if (ui->batterySlider->value() < batteryPercent) {
            ui->batterySlider->setValue(ui->batterySlider->value() + 1);
            sleepy(10);
        } else {
            ui->batterySlider->setValue(ui->batterySlider->value() - 1);
            sleepy(10);
        }
    }
    ui_initializeBattery();

    //START THERAPY - FLAG 1 TO INDICATE THERAPY AS RECORDING
    //(DO NOT RECORD THIS THERAPY)
    ui->log->append("**STARTING REPLAY**\n");
    therapy(group, session, 0, intensity);
}

// SLOT FUNCTIONS (UI EVENT HANDLERS)

// pressPower() is called when the UI power button is pressed (before release) - starts a timer to get the elapsed time between press and release ...
// so that we can differentiate between a button "press and release" and a button "press, hold, and release"
void MainWindow::pressPower(){
    powerPressedTimer.start();
}

void MainWindow::powerReleased(){
    // 1 of 4 uses of the power button - will end session early if pressed while in-session
    if(device->getIsInSession()){
        endSessionEarlyFlag = true;
        return;
    }

    if(powerPressedTimer.elapsed() >= 200){ // check if Power Button was held for 2 seconds
        if(!device->getIsPoweredOn() && !device->getIsSoftPoweredOn()){ // continue if DEVICE is OFF
            // 2 of 4 uses of the power button - turn on the device
            if (device->getFirstBoot()) {
                ui->connectionSlider->setEnabled(true);
                bootConnectionTest();

                //CHECK IF TIMED OUT
                if (device->getTimeout()) {
                    device->setTimeout(false);
                    return;
                }

                device->setFirstBoot(false);
            }

            ui_initializeBattery();
            if(device->getBattery()->getBatteryLevel() < 33){ // check if battery is too low to boot
                device->setSoftPower(true);
                device->getBattery()->setBlinkFlag(true);

                ui->log->append("Battery level too low. Replace Batteries");
                ui->log->append("");
                blinkBattery();
                return;
            }
            powerLightOnOff(true);
            changeBackgroundColor(ui->deltaButton, "green", "delta");
            changeBackgroundColor(ui->group20Button, "green", "20");

        // 3 of 4 uses of the power button - turn the device off
        } else { // continue if DEVICE is ON - turn off
            powerLightOnOff(false);
            turnOffUI();

            //ENSURE BOOT CONNECTION TEST
            device->setFirstBoot(true);
            ui->connectionSlider->setValue(1);
            connectionIntensity = 1;
            ui->connectionSlider->setEnabled(false);
        }

        device->getPowerButton()->pressed();
        changeConnectionSlider();
    // 4 of 4 uses of the power button - cycle between the group icons
    } else {
        cycleGroupButton();
    }
}

void MainWindow::pressUpArrow(){
    if (!device->getIsPoweredOn()) {return;}

    // 1 of 2 uses for the upArrowButton - if in session, buttons adjust intensity
    if(device->getIsInSession()){
        timesIntensityAdjusted++;
        if(device->getCurrentIntensity()==100){
            ui->log->append("\nWarning: Device's maximum intensity reached");
            displayIntensityOnGraph();
            return;
        }
        device->setCurrentIntensity(device->getCurrentIntensity()+1);
        updateIntensityLog();
        displayIntensityOnGraph();
        return;
    }

    // 2 of 2 uses for the upArrowButton - navigate through the Session types in UI
    switch (selectedSession) {
        //DELTA IS LIT UP, WE WANT THETA LIT INSTEAD
        case 1:
            changeBackgroundColor(ui->deltaButton, "white", "delta");
            changeBackgroundColor(ui->thetaButton, "green", "theta");
            selectedSession++;
        break;
        //THETA IS LIT UP, WE WANT ALPHA LIT INSTEAD
        case 2:
            changeBackgroundColor(ui->thetaButton, "white", "theta");
            changeBackgroundColor(ui->alphaButton, "green", "alpha");
            selectedSession++;
        break;
        //ALPHA IS LIT UP, WE WANT BETA LIT INSTEAD
        case 3:
            changeBackgroundColor(ui->alphaButton, "white", "alpha");
            changeBackgroundColor(ui->betaButton, "green", "beta");
            selectedSession++;
        break;
        //BETA IS LIT UP, WE WANT DELTA LIT INSTEAD
        case 4:
            changeBackgroundColor(ui->betaButton, "white", "beta");
            changeBackgroundColor(ui->deltaButton, "green", "delta");
            selectedSession = 1;
        break;
    }
}

void MainWindow::pressDownArrow(){
    if (!device->getIsPoweredOn()) {return;}

    // 1 of 2 uses for the downArrowButton - if in session, button decrements intensity
    if(device->getIsInSession()){
        timesIntensityAdjusted++;
        if(device->getCurrentIntensity()==1){
            ui->log->append("\nWarning: Device's minimum intensity reached");
            displayIntensityOnGraph();
            return;
        }
        device->setCurrentIntensity(device->getCurrentIntensity()-1);
        updateIntensityLog();
        displayIntensityOnGraph();
        return;
    }

    // 2 of 2 uses for the downArrowButton - navigate between Session types in UI
    switch (selectedSession) {
        //DELTA IS LIT UP, WE WANT BETA LIT INSTEAD
        case 1:
            changeBackgroundColor(ui->deltaButton, "white", "delta");
            changeBackgroundColor(ui->betaButton, "green", "beta");
            selectedSession = 4;
        break;
        //THETA IS LIT UP, WE WANT DELTA LIT INSTEAD
        case 2:
            changeBackgroundColor(ui->thetaButton, "white", "theta");
            changeBackgroundColor(ui->deltaButton, "green", "delta");
            selectedSession--;
        break;
        //ALPHA IS LIT UP, WE WANT THETA LIT INSTEAD
        case 3:
            changeBackgroundColor(ui->alphaButton, "white", "alpha");
            changeBackgroundColor(ui->thetaButton, "green", "theta");
            selectedSession--;
        break;
        //BETA IS LIT UP, WE WANT APLHA LIT INSTEAD
        case 4:
            changeBackgroundColor(ui->betaButton, "white", "beta");
            changeBackgroundColor(ui->alphaButton, "green", "alpha");
            selectedSession--;
        break;
    }
}

void MainWindow::pressSelect(){
    selectTimer.start();
}

void MainWindow::stopPressed() {
    device->setRecordingFlag(true);
}

void MainWindow::releaseSelect() {
    if (selectTimer.elapsed() >= 1000) {
        therapy(selectedGroup, selectedSession, 1);
    } else {
        therapy(selectedGroup, selectedSession, 0);
    }
}

void MainWindow::connectEarClips(){
    ui->connectionSlider->setValue(3);
    changeConnectionSlider();
}

void MainWindow::disconnectEarClips(){
    ui->connectionSlider->setValue(1);
    changeConnectionSlider();
}

void MainWindow::cycleGroupButton() {
    if (!device->getIsPoweredOn()) {return;}

    switch (selectedGroup) {
        //20 IS LIT UP, WE WANT 45 LIT INSTEAD
        case 1:
            changeBackgroundColor(ui->group20Button, "white", "20");
            changeBackgroundColor(ui->group45Button, "green", "45");
            selectedGroup++;
        break;
        //45 IS LIT UP, WE WANT USER LIT INSTEAD
        case 2:
            changeBackgroundColor(ui->group45Button, "white", "45");
            changeBackgroundColor(ui->groupUserButton, "green", "user");
            selectedGroup++;
        break;
        //USER IS LIT UP, WE WANT 20 LIT INSTEAD
        case 3:
            changeBackgroundColor(ui->groupUserButton, "white", "user");
            changeBackgroundColor(ui->group20Button, "green", "20");
            selectedGroup = 1;
        break;
    }
}

void MainWindow::changeConnectionSlider() {
    ui->graphLabel->setText("Currently indicating: Connection");

    connectionIntensity = ui->connectionSlider->value();
    if (!device->getIsPoweredOn()) {return;}

    switch (connectionIntensity) {
        //NO CONNECTION - TOP SECTION BLINKS
        case 1:
            changeTextColor(ui->connectionTop, "gray");
            changeTextColor(ui->connectionMiddle, "gray");
            changeTextColor(ui->connectionBottom, "gray");

            connectionTest();
        break;
        //OKAY CONNECTION - MIDDLE SECTION ON - ORANGE
        case 2:
            changeTextColor(ui->connectionTop, "gray");
            changeTextColor(ui->connectionMiddle, "orange");
            changeTextColor(ui->connectionBottom, "gray");
        break;
        //OKAY CONNECTION - BOTTOM SECTION ON - GREEN
        case 3:
            changeTextColor(ui->connectionTop, "gray");
            changeTextColor(ui->connectionMiddle, "gray");
            changeTextColor(ui->connectionBottom, "green");
        break;
    }
}

void MainWindow::changeBatterySlider(){
    device->getBattery()->setBatteryLevel(ui->batterySlider->value());
    if(device->getBattery()->getBatteryLevel()>32){
        device->getBattery()->setBlinkFlag(false);
    }
    ui_initializeBattery();
    ui->batteryLevel1->setStyleSheet("QTextBrowser {background-color: red;}");
}

// BATTERY HELPER FUNCTIONS
// drainBattery() is a vital function that simulates draining the device's battery based on intensity, connection, and duration
// it is called in the therapy() while loop, so this function just decrements the battery level by small values at a time
void MainWindow::drainBattery(int intensity){
    // Standard battery life on initialization is 100 units
    double drainRate = 0.25; // 0.5 is the base rate at which the battery depletes

    // Simulating the device to not drain too quickly.
    // at max intensity levels (>75hz) and strong connection status, battery will drain 2.5 units per loop
    // at weak intensity levels (<10hz) and strong connection status, battery wll drain 1 units per loop
    if(intensity>75){ drainRate +=2; }
    else if(intensity>50){ drainRate+=1.5; }
    else if(intensity>25){ drainRate+=1; }
    else if(intensity>10){ drainRate+=.5; }

    if(connectionIntensity==3){ drainRate += 0.25; } // strong connection yields higher efficiency
    else if(connectionIntensity==2){ drainRate += 0.5; } // medium connection yields more inefficient battery use

    device->getBattery()->setBatteryLevel(device->getBattery()->getBatteryLevel()-drainRate); // decrement battery life by 1 unit

    // Reflect battery life change on UI battery elements
    ui->batterySlider->setValue(device->getBattery()->getBatteryLevel());
    ui_initializeBattery();
}

// checkBattery() is a simple function that returns true if the battery level is sufficient to start the device or start a session (battery level must be >32 units)
bool MainWindow::checkBattery(){
    // if battery life is >32 units than Device can turn on and session can start
    if(device->getBattery()->getBatteryLevel()>32){ return true; }
    return false;
}

// batteryWarning() is called the battery level drops below 33 units during a session
void MainWindow::batteryWarning(){
    ui->log->append("\nBattery level too low. Replace Batteries");
    ui->log->append("Session will now end early. Device will now power down via Soft Off protocol.");
    device->getBattery()->setBlinkFlag(true);
    blinkBattery();
}

// ui_initializeBattery() is called to change the UI Battery icon according to the current battery level
void MainWindow::ui_initializeBattery(){
    sleepy(10);
    ui->batteryLevel1->setStyleSheet("QTextBrowser {background-color: red;}");
    if(device->getBattery()->getBatteryLevel()>=33){
        ui->batteryLevel2->setStyleSheet("QTextBrowser {background-color: yellow;}");
        if(device->getBattery()->getBatteryLevel()>=67){
                ui->batteryLevel3->setStyleSheet("QTextBrowser {background-color: green;}");
        } else{ ui->batteryLevel3->setStyleSheet("QTextBrowser {background-color: white;}"); }
    }else{ ui->batteryLevel2->setStyleSheet("QTextBrowser {background-color: white;}"); }
    ui->batteryLevel1->setStyleSheet("QTextBrowser {background-color: red;}");
}

// blinkBattery() is called when the battery level reaches <33 units, so that UI can notify the user to change the battery
void MainWindow::blinkBattery(){
    while (device->getBattery()->getBlinkFlag()) {
        ui->batteryLevel1->setStyleSheet("QTextBrowser {background-color: white;}");
        sleepy(100);
        ui->batteryLevel1->setStyleSheet("QTextBrowser {background-color: red;}");
        sleepy(100);
    }
    ui->batteryLevel1->setStyleSheet("QTextBrowser {background-color: red;}");
}

// OTHER HELPER FUNCTIONS
void MainWindow::changeBackgroundColor(QPushButton *button, const QString& color, const QString& image, const QString& radius){
    button->setStyleSheet("QPushButton {border-image: url(:/icons/" + image +".png); background-color: " + color + "; border-radius: " + radius + ";}");
}

void MainWindow::changeTextColor(QTextBrowser *text, QColor color) {
    text->setTextColor(color);
    text->setFontPointSize(18);
    text->setText(text->toPlainText());
}

void MainWindow::turnOffUI() {
    device->setSoftPower(false);

    //TURN OFF GROUP BUTTON
    switch (selectedGroup) {
        case 1:
            changeBackgroundColor(ui->group20Button, "white", "20");
        break;
        case 2:
            changeBackgroundColor(ui->group45Button, "white", "45");
        break;
        case 3:
            changeBackgroundColor(ui->groupUserButton, "white", "user");
        break;
    }

    //TURN OFF SESSION BUTTON
    switch (selectedSession) {
        case 1:
            changeBackgroundColor(ui->deltaButton, "white", "delta");
        break;
        case 2:
            changeBackgroundColor(ui->thetaButton, "white", "theta");
        break;
        case 3:
            changeBackgroundColor(ui->alphaButton, "white", "alpha");
        break;
        case 4:
            changeBackgroundColor(ui->betaButton, "white", "beta");
        break;
    }

    //TURN OFF CONNECTION INDICATOR
    switch (connectionIntensity) {
        case 1:
            changeTextColor(ui->connectionTop, "gray");
        break;
        case 2:
            changeTextColor(ui->connectionMiddle, "gray");
        break;
        case 3:
            changeTextColor(ui->connectionBottom, "gray");
        break;
    }

    //QUICKLY BREAK WHILE LOOP IN controlTest() IF IT IS BLINKING
    if (connectionIntensity == 1) {
        connectionIntensity = 2;
    }

    //QUICKLY BREAK WHILE LOOP IN blinkBattery() IF IT IS BLINKING
    if (device->getBattery()->getBlinkFlag()) {
        device->getBattery()->setBlinkFlag(false);
    }
    //TURN OFF BATTERY INDICATORS
    ui->batteryLevel1->setStyleSheet("QTextBrowser {background-color: white;}");
    ui->batteryLevel2->setStyleSheet("QTextBrowser {background-color: white;}");
    ui->batteryLevel3->setStyleSheet("QTextBrowser {background-color: white;}");

    //TURN OFF CES INDICATOR
    changeBackgroundColor(ui->CES2Button, "white", "CES2", "34");
}

void MainWindow::bootConnectionTest() {
    timeoutTimer.start();

    while (connectionIntensity == 1) {
        changeBackgroundColor(ui->CESButton, "green", "CES", "34");
        changeBackgroundColor(ui->CES2Button, "green", "CES2", "34");
        sleepy(100);
        changeBackgroundColor(ui->CESButton, "white", "CES", "34");
        changeBackgroundColor(ui->CES2Button, "white", "CES2", "34");
        sleepy(100);

        //CHECK FOR TIMEOUT - 2 MINS IS 120000 MS
        if (timeoutTimer.elapsed() >= 15000) {
            ui->log->append("**DEVICE TIMED OUT**");
            device->setTimeout(true);
            return;
        }
    }
    changeBackgroundColor(ui->CES2Button, "green", "CES2", "34");
}

// softOff() is called when a session is ended early - decreases the intensity to it's lowest setting before powering off as per the Soft Off feature requirements
void MainWindow::softOff(){
    while(device->getCurrentIntensity()>1){
        device->setCurrentIntensity(device->getCurrentIntensity()-1);
        updateIntensityLog();
        sleepy(50);
    }
    displayIntensityOnGraph();
}

// blinkSession() is called before a session is started - it will cause the selected Session icon to blink for a couple seconds before the session starts, to notify the user of the session they've locked in
void MainWindow::blinkSession(int sessionNum){
    bool flag = true;
    QString sessionType = "";
    QPushButton* button;

    switch(sessionNum) {
        case 1:
            sessionType = "delta";
            button = ui->deltaButton;
        break;
        case 2:
            sessionType = "theta";
            button = ui->thetaButton;
        break;
        case 3:
            sessionType = "alpha";
            button = ui->alphaButton;
        break;
        case 4:
            sessionType = "beta";
            button = ui->betaButton;
        break;
    }

    for(int i=10; i>0; i--){
        if(flag){
            changeBackgroundColor(button, "white", sessionType);
            flag = false;
            sleepy(150);
            continue;
        }
        changeBackgroundColor(button, "green", sessionType);
        flag = true;
        sleepy(150);
    }

    changeBackgroundColor(button, "green", sessionType);
}

void MainWindow::addUserButtonClicked() {
    //STOP USER FROM ADDING USERS IF DEVICE IS OFF
    if (!device->getIsPoweredOn()) {return;}

    //GET VALUES FROM INPUT FIELDS
    string name = ui->userNameInput->toPlainText().toStdString();
    int duration = ui->userDurationInput->toPlainText().toInt();

    //CHECK IF USER ALREADY EXISTS UNDER THAT NAME
    if (device->getUserByName(name)) {
        ui->log->append("**USER " + QString::fromStdString(name) + " ALREADY EXISTS**");
        return;
    }

    //CHECK IF USER SPECIFIED BAD INPUT
    if (name == "" || duration == 0) {
        ui->log->append("**COULD NOT ADD USER - BAD INPUT**");
        return;
    //CHECK IF MAX NUMBER OF USERS IS REACHED
    } else if (device->addUser(name, duration) == -1) {
        ui->log->append("**COULD NOT ADD USER - MAX USERS**");

        //CLEAR INPUT FIELDS
        ui->userNameInput->clear();
        ui->userDurationInput->clear();
        return;
    //USER ADDED SUCCESSFULLY
    } else {
        ui->log->append("**ADDED USER " + QString::fromStdString(name) + "**");

        //CLEAR INPUT FIELDS
        ui->userNameInput->clear();
        ui->userDurationInput->clear();
    }

    //ADD NEW USER TO NAME COMBO BOX
    ui->nameComboBox->addItem(QString::fromStdString(name));
}

void MainWindow::addRecording(const string& name, int group, int batteryPercent, int initialIntensity, int intensity) {
    //CHECK IF WE ARE USING DEFAULT INTENSITY
    if (intensity == -1) { intensity = device->getSessions(group-1, selectedSession-1)->getIntensity(); }

    if (device->addRecording(name, intensity, initialIntensity, group, batteryPercent, connectionIntensity) == -1) {
        ui->log->append("**COULD NOT ADD RECORDING - MAX RECORDINGS**\n");
        return;
    } else {
        ui->log->append("**ADDED RECORDING UNDER USER " + QString::fromStdString(name) + "**\n");
    }
}

void MainWindow::printHistoryButtonClicked() {
    string name = ui->nameComboBox->currentText().toStdString();

    ui->log->append("**PRINTING HISTORY OF USER " + QString::fromStdString(name) + "**");

    int numRecordings = 0;
    for (int i = 0; i < device->getNumRecordings(); i++) {
        Recording* recording = device->getRecordingAt(i);
        if (recording->getName() == name) {
            if (numRecordings == 0) {ui->historySpinBox->setMinimum(1);}
            numRecordings++;

            int intensity = recording->getIntensity();
            int group = recording->getGroup();
            int duration;

            switch (group) {
                case 1: duration = 20;
                break;
                case 2: duration = 45;
                break;
                case 3: duration = device->getUserByName(name)->getDuration();
                break;
            }

            ui->log->append(QString::number(numRecordings) + ".\t INTENSITY: " + QString::number(intensity) + "\n\t DURATION: " + QString::number(duration));
        }
    }
    ui->historySpinBox->setMaximum(numRecordings);

    if (numRecordings == 0) {ui->log->append("**USER " + QString::fromStdString(name) + " HAS NO TREATMENT HISTORY**\n");}
}

// setTherapyLock() function used to enable and disable Connection, Intensity, and Power setting UI elements, as to not let the user interrupt a process (works well (-_^))
void MainWindow::setTherapyLock(bool status){
    ui->connectEarclipsButton->setEnabled(status);
    ui->disconnectEarclipsButton->setEnabled(status);
    ui->connectionSlider->setEnabled(status);

    ui->upArrowButton->setEnabled(status);
    ui->downArrowButton->setEnabled(status);
    ui->powerButton->setEnabled(status);
}

//USE STATE OF CONTROL WINDOW TO DETERMINE THE DESIRED RECORDING

void MainWindow::playReplayButtonClicked() {
    //GET RECORDING NUMBER OF SPECIFIED USER, DO NOTHING IF 0
    int desiredNum = ui->historySpinBox->value();
    if (desiredNum == 0) { return; }

    //GET USER NAME
    string name = ui->nameComboBox->currentText().toStdString();
    Recording* desiredRecording;

    //LOOP THROUGH EACH RECORDING, COUNTING NUMBER OF RECORDINGS
    //OF SPECIFIED USER, STOP WHEN COUNT IS EQUAL TO DESIRED NUM
    int counter = 0;
    for (int i = 0; i < device->getNumRecordings(); i ++) {
        if (device->getRecordingAt(i)->getName() == name) {
            counter++;
            if (counter == desiredNum) {
                desiredRecording = device->getRecordingAt(i);
                break;
            }
        }
    }

    //REPLAY THE DESIRED RECORDING
    replayRecording(desiredRecording);
}

void MainWindow::updateIntensityLog(){
    QString text = "";
    text.append(QString::number(device->getCurrentIntensity()));
    ui->currentIntensityLog->setText(text);
}

// displayIntensityOnGraph() is used to have the graph blink the relative intensity level
// note that everytime that the intensity level is changed during a session, this function (the UI animation this function does) ...
// consumes 750ms of the therapy time... (5 x (sleepy(75) x 2)) = 750ms per call
// this loss in time is made up for within the therapy() function
void MainWindow::displayIntensityOnGraph(){
    ui->graphLabel->setText("Currently indicating: Intensity");
    changeTextColor(ui->connectionTop, "gray");
    changeTextColor(ui->connectionMiddle, "gray");
    changeTextColor(ui->connectionBottom, "gray");

    for(int i=0; i<5; i++){
        if(device->getCurrentIntensity()>66){
            changeTextColor(ui->connectionTop, "red");
            sleepy(75);
            changeTextColor(ui->connectionTop, "gray");
            sleepy(75);
        }
        else if(device->getCurrentIntensity()>32){
            changeTextColor(ui->connectionMiddle, "yellow");
            sleepy(75);
            changeTextColor(ui->connectionMiddle, "gray");
            sleepy(75);
        }
        else{
            changeTextColor(ui->connectionBottom, "green");
            sleepy(75);
            changeTextColor(ui->connectionBottom, "gray");
            sleepy(75);
        }
    }
    changeConnectionSlider();
}

// powerLightOnOff used to toggle the UI power light (above the power button)
void MainWindow::powerLightOnOff(bool status){
    if(status){
        ui->powerLight->setStyleSheet("QTextEdit {background-color: green;}");
        device->getPowerLight()->setIsLightOn(status);
        return;
    }
    ui->powerLight->setStyleSheet("QTextEdit {background-color: white;}");
    device->getPowerLight()->setIsLightOn(status);
}

// endSessionEarly() is called in response to the power button being pressed during a session
void MainWindow::endSessionEarly(){
    ui->log->append("Power button pressed.");
    ui->log->append("\nSession will now end early. Device will now power down via Soft Off protocol.");
    device->setIsInSession(false);
    softOff();
}

// sleepy() is used plenty throughout the implementation to simulate real-time waiting, as well as inside loops to make them iterate slower
void MainWindow::sleepy(int sleepTime) {
    QTime dieTime = QTime::currentTime().addMSecs(sleepTime);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

// TESTING SLOTS

void MainWindow::testAddUserClicked() {
    if (!device->getIsPoweredOn()) {return;}

    ui->testLog->append("**TESTING ADD USER FUNCTIONALITY**\nFILLING IN NAME AND DURATION FIELDS...");
    sleepy(100);

    ui->userNameInput->clear();
    ui->userNameInput->appendPlainText("User " + QString::number(device->getNumUsers() + 1));
    sleepy(100);

    ui->userDurationInput->clear();
    ui->userDurationInput->appendPlainText(QString::number((rand() % 20) + 1));
    sleepy(300);

    ui->testLog->append("CLICKING ADD USER BUTTON...");
    sleepy(100);

    addUserButtonClicked();
    ui->testLog->append("**TEST COMPLETE**\n");
}

void MainWindow::testAddBadUserClicked() {
    if (!device->getIsPoweredOn()) {return;}

    //EMPTY NAME
    ui->testLog->append("**TESTING ADD USER FUNCTIONALITY**\nADDING USER WITH EMPTY NAME...");
    sleepy(100);

    ui->userNameInput->clear();
    sleepy(100);

    ui->userDurationInput->clear();
    ui->userDurationInput->appendPlainText(QString::number((rand() % 20) + 1));
    sleepy(300);

    ui->testLog->append("CLICKING ADD USER BUTTON...");
    sleepy(1000);

    addUserButtonClicked();

    //STRING DURATION/EMPTY DURATION
    ui->testLog->append("ADDING USER WITH STRING DURATION...");
    sleepy(100);

    ui->userNameInput->clear();
    ui->userNameInput->appendPlainText("User " + QString::number(device->getNumUsers() + 1));
    sleepy(100);

    ui->userDurationInput->clear();
    ui->userDurationInput->appendPlainText("wym duration??");
    sleepy(3000);

    ui->testLog->append("CLICKING ADD USER BUTTON...");
    sleepy(1000);

    addUserButtonClicked();

    //DUPLICATE NAME - ENSURE THAT USER 1 ALREADY EXISTS
    ui->testLog->append("ADDING USER WITH DUPLICATE NAME...\n(ENSURE THAT USER 1 ALREADY EXISTS)");
    sleepy(100);

    ui->userNameInput->clear();
    ui->userNameInput->appendPlainText("User 1");
    sleepy(100);

    ui->userDurationInput->clear();
    ui->userDurationInput->appendPlainText(QString::number((rand() % 20) + 1));
    sleepy(3000);

    ui->testLog->append("CLICKING ADD USER BUTTON...");
    sleepy(1000);

    addUserButtonClicked();

    ui->testLog->append("**TEST COMPLETE**\n");
}

void MainWindow::testTherapyClicked() {
    if (!device->getIsPoweredOn()) {return;}

    ui->testLog->append("**TESTING THERAPY FUNCTIONALITY**\nSELECTING RANDOM GROUP AND SESSION...");
    sleepy(100);

    for (int i = 0; i < (rand() % 6) + 1; i++) {
        pressUpArrow();
        sleepy(200);
    }

    for (int i = 0; i < (rand() % 6) + 1; i++) {
        cycleGroupButton();
        sleepy(200);
    }

    ui->testLog->append("STARTING THERAPY SESSION...");
    therapy(selectedGroup, selectedSession, 0);
    ui->testLog->append("**TEST COMPLETE**\n");
}

void MainWindow::testRecordTherapyClicked() {
    if (!device->getIsPoweredOn()) {return;}

    ui->testLog->append("**TESTING RECORD THERAPY FUNCTIONALITY**\nSELECTING RANDOM GROUP AND SESSION...");
    sleepy(100);

    for (int i = 0; i < (rand() % 6) + 1; i++) {
        pressUpArrow();
        sleepy(200);
    }

    for (int i = 0; i < (rand() % 6) + 1; i++) {
        cycleGroupButton();
        sleepy(200);
    }

    ui->testLog->append("STARTING RECORDED THERAPY SESSION...");
    therapy(selectedGroup, selectedSession, 1);

    ui->testLog->append("**TEST COMPLETE**\n");
}

void MainWindow::testReplayClicked() {
    if (!device->getIsPoweredOn()) {return;}

    ui->testLog->append("**TESTING REPLAY FUNCTIONALITY**\nPRINTING USER'S REPLAY HISTORY...");
    sleepy(100);

    printHistoryButtonClicked();
    sleepy(1000);

    if (ui->historySpinBox->maximum() == 0) {
        ui->testLog->append("CANNOT PLAY REPLAY - USER HAS NO HISTORY...\n**TEST COMPLETE**\n");
        return;
    }

    ui->testLog->append("SELECTING RANDOM REPLAY...");
    ui->historySpinBox->setValue((rand() % ui->historySpinBox->maximum()) + 1);
    sleepy(100);

    ui->testLog->append("STARTING REPLAY...");
    sleepy(100);
    playReplayButtonClicked();

    ui->testLog->append("**TEST COMPLETE**\n");
}

void MainWindow::testOnlyRecordHelper() {
    testingTimer.restart();

    while (testingTimer.elapsed() < 1000) {}
    stopPressed();
    return;
}

void MainWindow::testOnlyRecordClicked() {
    if (!device->getIsPoweredOn()) {return;}

    ui->testLog->append("**TESTING ONLY RECORD FUNCTIONALITY**");

    if (ui->nameComboBox->currentText() == NULL) {
        ui->testLog->append("THIS TEST REQUIRES A USER TO BE SPECIFIED...\n**TEST COMPLETE**\n");
        return;
    }

    ui->testLog->append("STARTING RECORDED SESSION TO BE CANCELED AFTER 1 SECOND...");
    sleepy(100);

    std::thread first (&MainWindow::testOnlyRecordHelper, this);
    therapy(selectedGroup, selectedSession, 1);
    first.join();
    ui->testLog->append("CANCELING RECORDED SESSION...\n**TEST COMPLETE**\n");
}

void MainWindow::testLostConnectionClicked() {
    if (!device->getIsPoweredOn()) {return;}

    ui->testLog->append("**TESTING LOST CONNECTION FUNCTIONALITY**\nSTARTING A SESSION TO BE INTURUPTED...");
    sleepy(100);

    while (selectedGroup != 1) { cycleGroupButton(); sleepy(100);}
    while (selectedSession != 1) { pressUpArrow(); sleepy(100); }

    ui->testLog->append("ONCE THE \"Disconnect Earclips\" BUTTON BECOMES AVAILABLE, CLICK IT!");
    ui->testLog->append("AFTER THE CONNECTION LIGHTS STOP FLASHING, CLICK THE \"Connect Earclips\" BUTTON!");
    therapy(selectedGroup, selectedSession, 0);

    ui->testLog->append("**TEST COMPLETE**\n");
}

void MainWindow::testChangingIntensityClicked() {
    if (!device->getIsPoweredOn()) {return;}

    ui->testLog->append("**TESTING CHANGING INENSITY FUNCTIONALITY**");

    if (ui->nameComboBox->currentText() == NULL) {
        ui->testLog->append("THIS TEST REQUIRES A USER TO BE SPECIFIED...\n**TEST COMPLETE**\n");
        return;
    }

    ui->testLog->append("STARTING A SESSION TO BE RECORDED AND HAVE INTENSITY UPDATED...");
    sleepy(100);

    while (selectedGroup != 2) { cycleGroupButton(); sleepy(100);}
    while (selectedSession != 1) { pressUpArrow(); sleepy(100); }

    ui->testLog->append("ONCE THE CONSOLE LOG REPORTS COMPLETES IT'S COUNTDOWN, CLICK THE UP/DOWN BUTTON TO OBSERVE THE CHANGES IN INTENSITY!");
    therapy(selectedGroup, selectedSession, 1);

    ui->testLog->append("NOW OBSERVE THE PRINTED HISTORY TO ENSURE THAT THE HIGHEST RECORDED INTENSITY WAS SAVED!");
    printHistoryButtonClicked();

    ui->testLog->append("**TEST COMPLETE**\n");
}

void MainWindow::testDepleteBatteryClicked() {
    if (!device->getIsPoweredOn()) {return;}

    ui->testLog->append("**TESTING DEPLETE BATTERY FUNCTIONALITY**");

    while (selectedGroup != 2) { cycleGroupButton(); sleepy(100); }

    ui->testLog->append("STARTING THERAPY SESSION...\nONCE THE BATTERY IS DEPLETED, DRAG THE \"Battery Level\" SLIDER TO THE RIGHT TO COMPLETE THE TEST!");

    therapy(selectedGroup, selectedSession, 0, 99);

    ui->testLog->append("**TEST COMPLETE**\n");
}
