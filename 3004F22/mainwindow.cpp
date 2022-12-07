#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    device = new Device("oasis pro");

    ui->batterySlider->setValue(device->getBattery()->getBatteryLevel());

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
}

MainWindow::~MainWindow() {
    delete ui;
    delete device;
}

void MainWindow::powerReleased(){
    if(elapsedTimer.elapsed() >= 200){ // check if Power Button was held for 2 seconds
        if(!device->getIsPoweredOn() && !device->getIsSoftPoweredOn()){ // continue if DEVICE is OFF
            if (device->getFirstBoot()) {
                ui->connectionSlider->setEnabled(true);
                bootConnectionTest();

                //CHECK IF TIMED OUT
                if (device->getTimeout()) {
                    cout << "DEVICE TIMED OUT" << endl;
                    device->setTimeout(false);
                    return;
                }

                device->setFirstBoot(false);
            }

            ui_initializeBattery();
            if(device->getBattery()->getBatteryLevel() < 33){
                device->setSoftPower(true);
                device->getBattery()->setBlinkFlag(true);

                ui->log->append("Battery level too low. Replace Batteries");
                ui->log->append("");
                blinkBattery();
                return;
            }
            changeBackgroundColor(ui->deltaButton, "green", "delta");
            changeBackgroundColor(ui->group20Button, "green", "20");
        } else { // continue if DEVICE is ON - turn off
            turnOff();

            //ENSURE BOOT CONNECTION TEST
            device->setFirstBoot(true);
            ui->connectionSlider->setValue(1);
            connectionIntensity = 1;
            ui->connectionSlider->setEnabled(false);
        }

        device->getPowerButton()->pressed();
        changeConnectionSlider();
    } else {
        cycleGroupButton();
    }
}

void MainWindow::turnOff() {
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

// pressPower() is called when the UI power button is pressed (before release) - starts a timer to get the elapsed time between press and release ...
// so that we can differentiate between a button "press and release" and a button "press, hold, and release"
void MainWindow::pressPower(){
    elapsedTimer.start();
}

void MainWindow::pressUpArrow(){
    if (!device->getIsPoweredOn()) {return;}

    // 1 of 2 uses for the upArrowButton - if in session, buttons adjust intensity
    if(device->getIsInSession()){
        timesIntensityAdjusted++;
        if(device->getCurrentIntensity()==100){
            ui->log->append("Warning: Device's maximum intensity reached");
            ui->log->append("");
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
            ui->log->append("Warning: Device's minimum intensity reached");
            ui->log->append("");
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

void MainWindow::releaseSelect() {
    if (selectTimer.elapsed() >= 1000) {
        therapy(selectedGroup, selectedSession, 1);
    } else {
        therapy(selectedGroup, selectedSession, 0);
    }
}

void MainWindow::stopPressed() {
    device->setRecordingFlag(true);
}

// therapy() is the provides the main functionality of the device - initiating and performing therapy sessions
void MainWindow::therapy(int groupNum, int sessionNum, int recordingFlag, int overrideIntensity){
    string name = ui->nameComboBox->currentText().toStdString();
    int group = selectedGroup;
    int initialIntensity = device->getSessions(selectedGroup-1, selectedSession-1)->getIntensity();
    double batteryPercent = device->getBattery()->getBatteryLevel();

    if (recordingFlag) {
        if (ui->nameComboBox->currentText() == NULL) {
            ui->log->append("CANNOT RECORD - NO USER SPECIFIED");
            recordingFlag = 0;
        } else {
            ui->log->append("THIS SESSION WILL BE RECORDED UNDER USER " + QString::fromStdString(name));

            //CHECK IF USER WANTS TO JUST RECORD, OR DO SESSION AT THE SAME TIME
            changeBackgroundColor(ui->stopButton, "green", "stop", "20");
            sleepy(1);

            device->setRecordingFlag(false);
            pauseTimer.restart();
            pauseTimer.start();
            while (pauseTimer.elapsed() < 5000){
                sleepy(1);
                if (device->getRecordingFlag()) {
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
        ui->log->append("Connection level is poor. Please adjust.");
        ui->log->append("");
        return;
    }
    setConnectionLock(false); // lock all Connection setting UI until Session begins

    device->setIsInSession(true);
    ui->log->append("Therapy session will begin in 5 seconds:");
    blinkSession(sessionNum); // make the session icon blink for a couple seconds

    // Begin session with blinking session icon and 5 second count down
    for(int i=5; i>0; i--){
        QString text = "";
        text.append(QString::number(i));
        ui->log->append(text);
        sleepy(100); // small sleep to simulate count down
    }
    ui->log->append("");

    int therapyLengthMS = device->getGroups(groupNum-1)->getLengthMS(); // get Group's associated therapy time length (in milliseconds)

    //SET CURRENT DEVICE INTENSITY ACCORDING TO OVERWRITEN VALUE - USED FOR RECORDING REPLAY
    if (overrideIntensity == -1) {
        device->setCurrentIntensity(device->getSessions(groupNum-1, sessionNum-1)->getIntensity());
    } else {
        device->setCurrentIntensity(overrideIntensity);
    }

    updateIntensityLog(); // update Intensity log in UI

    setConnectionLock(true); // unlock Connection setting UI

    therapyTimer.start(); // Timer tracks elapsed time
    int remainingTime = 0;
    timesIntensityAdjusted = 0;
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

        // During each loop (where the Device is not disconnected) record how long remains of the session
        if(connectionIntensity!=1){
            remainingTime = therapyLengthMS - therapyTimer.elapsed();
        }

        // This loop functions such that if the Device disconnects during a session, the device will wait until Connection returns and sets a flag to let the Device know it needs to resume a session
        while(connectionIntensity==1){
            flag = 1;
            ui->log->append("Connection level is poor. Please adjust."); // prompt user to reconnect
            ui->log->append("");
            sleepy(2000);
        }

        if(flag){ // return to session
            ui->log->append("Resuming Session.");
            ui->log->append("");
            therapyTimer.restart(); // restart and begin timer again
            while(therapyTimer.elapsed() < remainingTime){ // execute the remaining time of the session
                // Battery level must be checked inside this loop as well
                if(!checkBattery()){
                    batteryWarning();
                    device->setIsInSession(false);;
                    return;
                }
                if(timesIntensityAdjusted){
                    therapyLengthMS+(750*timesIntensityAdjusted);
                    timesIntensityAdjusted=0;
                }
                drainBattery(device->getCurrentIntensity()); // deplete battery
                sleepy(150); // simulate real time
                cout << device->getBattery()->getBatteryLevel() << endl; // monitor the battery level in the output
            }
            ui->log->append("Session Complete."); // log to control that session has completed
            ui->log->append("");
            device->setIsInSession(false);
            break; // session ends, break therapy loop
        }

        // Remainder of this function executes if session does not disconnect (standard use case)
        drainBattery(device->getCurrentIntensity());
        sleepy(150);
        cout << device->getBattery()->getBatteryLevel() << endl;
        if(therapyTimer.elapsed() >= therapyLengthMS && connectionIntensity!=1){
            //DO RECORDING HERE
            if (recordingFlag) {addRecording(name, group, batteryPercent, initialIntensity, highestIntensity);}

            ui->log->append("Session Complete.");
            device->setIsInSession(false);
            break; // session ends, break therapy loop
        }
    }
}

void MainWindow::drainBattery(int intensity) {
    // Standard battery life on initialization is 100 units
    double drainRate = 0.5; // 0.5 is the base rate at which the battery depletes

    // Simulating the device to not drain too quickly. Around max intensity battery will drain 2.5 units per loop
    if(intensity>75){drainRate +=2;}
    else if(intensity>50){drainRate+=1.5;}
    else if(intensity>25){drainRate+=1;}
    else if(intensity>10){drainRate+=.5;}

    device->getBattery()->setBatteryLevel(device->getBattery()->getBatteryLevel()-drainRate); // decrement battery life by 1 unit

    // Reflect battery life change on UI battery elements
    ui->batterySlider->setValue(device->getBattery()->getBatteryLevel());
    ui_initializeBattery();
}

bool MainWindow::checkBattery(){
    // if battery life is >32 units than Device can turn on and session can start
    if(device->getBattery()->getBatteryLevel()>32){ return true; }
    return false;
}

void MainWindow::batteryWarning(){
    ui->log->append("Battery level too low. Replace Batteries");
    ui->log->append("");
    ui->log->append("Session will now end early. Device will now power down via Soft Off protocol.");
    device->getBattery()->setBlinkFlag(true);
    blinkBattery();
}

void MainWindow::changeBackgroundColor(QPushButton *button, const QString& color, const QString& image, const QString& radius) {
    button->setStyleSheet("QPushButton {border-image: url(:/icons/" + image +".png); background-color: " + color + "; border-radius: " + radius + ";}");
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
}

void MainWindow::changeTextColor(QTextBrowser *text, QColor color) {
    text->setTextColor(color);
    text->setFontPointSize(18);
    text->setText(text->toPlainText());
}

// connectionTest function (previously blinkTopSection()) makes Connection UI elements flash to indicate Connection status
void MainWindow::connectionTest() {
    ui->graphLabel->setText("Currently indicating: Connection");
    ui->log->append("Connection lost. Please try again in a moment."); // report connection loss to control log
    ui->log->append("");

    setConnectionLock(false); // lock connection UI components for a moment

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
    ui->log->append("Please connect now.");
    ui->log->append("");
    setConnectionLock(true); // unlock the UI connection components
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

void MainWindow::blinkBattery(){
    while (device->getBattery()->getBlinkFlag()) {
        ui->batteryLevel1->setStyleSheet("QTextBrowser {background-color: white;}");
        sleepy(100);
        ui->batteryLevel1->setStyleSheet("QTextBrowser {background-color: red;}");
        sleepy(100);
    }
    ui->batteryLevel1->setStyleSheet("QTextBrowser {background-color: white;}");
}

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

void MainWindow::ui_initializeBattery(){
    ui->batteryLevel1->setStyleSheet("QTextBrowser {background-color: red;}");
    if(device->getBattery()->getBatteryLevel()>=33){
        ui->batteryLevel2->setStyleSheet("QTextBrowser {background-color: yellow;}");
        if(device->getBattery()->getBatteryLevel()>=67){
                ui->batteryLevel3->setStyleSheet("QTextBrowser {background-color: green;}");
        } else{ ui->batteryLevel3->setStyleSheet("QTextBrowser {background-color: white;}"); }
    }else{ ui->batteryLevel2->setStyleSheet("QTextBrowser {background-color: white;}"); }
}

void MainWindow::sleepy(int sleepTime) {
    QTime dieTime = QTime::currentTime().addMSecs(sleepTime);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::connectEarClips(){
    ui->connectionSlider->setValue(3);
    changeConnectionSlider();
}

void MainWindow::disconnectEarClips(){
    ui->connectionSlider->setValue(1);
    changeConnectionSlider();
}

void MainWindow::addUserButtonClicked() {
    if (!device->getIsPoweredOn()) {return;}

    string name = ui->userNameInput->toPlainText().toStdString();
    int duration = ui->userDurationInput->toPlainText().toInt();

    if (device->getUserByName(name)) {
        ui->log->append("**USER " + QString::fromStdString(name) + " ALREADY EXISTS**");
        return;
    }

    if (name == "" || duration == 0) {
        ui->log->append("**COULD NOT ADD USER - BAD INPUT**");
        return;
    } else if (device->addUser(name, duration) == -1) {
        ui->log->append("**COULD NOT ADD USER - MAX USERS**");
        return;
    } else {
        ui->log->append("**ADDED USER " + QString::fromStdString(name) + "**");
    }

    ui->nameComboBox->addItem(QString::fromStdString(name));
}

void MainWindow::addRecording(const string& name, int group, int batteryPercent, int initialIntensity, int intensity) {
    //CHECK IF WE ARE USING DEFAULT INTENSITY
    if (intensity == -1) { intensity = device->getSessions(group-1, selectedSession-1)->getIntensity(); }

    if (device->addRecording(name, intensity, initialIntensity, group, batteryPercent, connectionIntensity) == -1) {
        ui->log->append("**COULD NOT ADD RECORDING**");
        return;
    } else {
        ui->log->append("**ADDED RECORDING UNDER USER " + QString::fromStdString(name) + "**");
    }
}

void MainWindow::printHistoryButtonClicked() {
    string name = ui->nameComboBox->currentText().toStdString();

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
}

// setConnectionLock() function used to enable and disable Connection UI elements, as to not let the user interrupt a process (works well (-_^))
void MainWindow::setConnectionLock(bool status){
    ui->connectEarclipsButton->setEnabled(status);
    ui->disconnectEarclipsButton->setEnabled(status);
    ui->connectionSlider->setEnabled(status);
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

//REPLAY THE RECORDING SPECIFIED IN CONTROL WINDOW
void MainWindow::replayRecording(Recording *recording) {
    ui->log->append("\n**SETTING MACHINE STATE FOR REPLAY**");

    //GRAB PARAMETERS FROM RECORDING OBJECT
    int group = recording->getGroup();
    int initialIntensity = recording->getInitialIntensity();
    int intensity = recording->getIntensity();
    double batteryPercent = recording->getBatteryPercent();
    int connection = recording->getConnection();
    int session;

    cout << initialIntensity << endl;

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
