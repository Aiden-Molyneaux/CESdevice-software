#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    device = new Device("TimeToLive");

    ui->batterySlider->setValue(device->getBattery()->getBatteryLevel());

    connect(ui->powerButton, SIGNAL(pressed()), this, SLOT (pressPower()));
    connect(ui->powerButton, SIGNAL(released()), this, SLOT (powerReleased()));
    connect(ui->upArrowButton, SIGNAL(released()), this, SLOT (pressUpArrow()));
    connect(ui->downArrowButton, SIGNAL(released()), this, SLOT (pressDownArrow()));
    connect(ui->connectionSlider, SIGNAL(sliderReleased()), this, SLOT (changeConnectionSlider()));
    connect(ui->batterySlider, SIGNAL(sliderReleased()), this, SLOT (changeBatterySlider()));
    connect(ui->checkButton, SIGNAL(released()), this, SLOT (pressSelect()));
    connect(ui->connectEarclipsButton, SIGNAL(released()), this, SLOT (connectEarClips()));
    connect(ui->disconnectEarclipsButton, SIGNAL(released()), this, SLOT (disconnectEarClips()));
    connect(ui->addUserButton, SIGNAL(released()), this, SLOT (addUserButtonClicked()));
    connect(ui->addFakeRecordingButton, SIGNAL(released()), this, SLOT (addRecordingButtonClicked()));
    connect(ui->printHistoryButton, SIGNAL(released()), this, SLOT (printHistoryButtonClicked()));
    connect(ui->playReplayButton, SIGNAL(released()), this, SLOT (playReplayButtonClicked()));
}

MainWindow::~MainWindow() {
    delete ui;
    delete device;
}

void MainWindow::powerReleased(){
    if(elapsedTimer.elapsed() >= 200){ // check if Power Button was held for 2 seconds
        if(!device->getIsPoweredOn() && !device->getIsSoftPoweredOn()){ // continue if DEVICE is OFF
            ui_initializeBattery();
            if(device->getBattery()->getBatteryLevel() < 33){
                device->setSoftPower(true);
                device->getBattery()->setBlinkFlag(true);

                ui->log->append("Battery level too low. Replace Batteries");
                blinkBattery();
                return;
            }
            changeBackgroundColor(ui->deltaButton, "green", "delta");
            changeBackgroundColor(ui->group20Button, "green", "20");
        } else { // continue if DEVICE is ON - turn off
            turnOff();
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

    //TURN OFF BATERY INDICATORS
    ui->batteryLevel1->setStyleSheet("QTextBrowser {background-color: white;}");
    ui->batteryLevel2->setStyleSheet("QTextBrowser {background-color: white;}");
    ui->batteryLevel3->setStyleSheet("QTextBrowser {background-color: white;}");
}

void MainWindow::pressPower(){
    elapsedTimer.start();
}

void MainWindow::pressUpArrow(){
    if (!device->getIsPoweredOn()) {return;}

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
    therapy(selectedGroup, selectedSession, 0);
}

void MainWindow::therapy(int groupNum, int sessionNum, int recordingFlag){
    if (ui->recordSessionRadioButton->isChecked() && !recordingFlag) { addRecordingButtonClicked(); }

    // Initial check to see if Battery needs to be replaced
    if(!checkBattery()){
        ui->log->append("Battery level too low. Replace Batteries");
        return;
    }

    // Also check the connection strength
    if(connectionIntensity==1){
        ui->log->append("Connection level is poor. Please adjust.");
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

    int therapyLengthMS = device->getGroups(groupNum-1)->getLengthMS(); // get Group's associated therapy time length (in milliseconds)
    device->setCurrentIntensity(device->getSessions(groupNum-1, sessionNum-1)->getIntensity());
//    int sessionIntensity = device->getCurrentIntensity();

    setConnectionLock(true); // unlock Connection setting UI

    therapyTimer.start(); // Timer tracks elapsed time
    int remainingTime = 0;
    while(true){
        int flag = 0; // flag for if Session pauses due to Connection interruption

        // Check that Battery levels are sufficient - if not, end the session early
        if(!checkBattery()){
            ui->log->append("Battery level too low. Replace Batteries");
            ui->log->append("Session will now end early. Device will now power down via Soft Off protocol.");
            return;
        }

        // During each loop (where the Device is not disconnected) record long remains of the session
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
            therapyTimer.restart(); // restart and begin timer again
            while(therapyTimer.elapsed() < remainingTime){ // execute the remaining time of the session
                drainBattery(device->getCurrentIntensity()); // deplete battery
                sleepy(150); // simulate real time
                cout << device->getBattery()->getBatteryLevel() << endl; // monitor the battery level in the output
            }
            ui->log->append("Session Complete."); // log to control that session has completed
            device->setIsInSession(false);
            break; // session ends, break therapy loop
        }

        // Remainder of this function executes if session does not disconnect (standard use case)
        drainBattery(device->getCurrentIntensity());
        sleepy(150);
        cout << device->getBattery()->getBatteryLevel() << endl;
        if(therapyTimer.elapsed() >= therapyLengthMS && connectionIntensity!=1){
            ui->log->append("Session Complete.");
            device->setIsInSession(false);
            break; // session ends, break therapy loop
        }
    }
}

void MainWindow::drainBattery(int intensity){
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

void MainWindow::changeBackgroundColor(QPushButton *button, const QString& color, const QString& image) {
    button->setStyleSheet("QPushButton {border-image: url(:/icons/" + image +".png); background-color: " + color + "; border-radius: 40;}");
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
    if (!device->getIsPoweredOn()) {return;}
    connectionIntensity = ui->connectionSlider->value();

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
    ui_initializeBattery();
}

void MainWindow::changeTextColor(QTextBrowser *text, QColor color) {
    text->setTextColor(color);
    text->setFontPointSize(18);
    text->setText(text->toPlainText());
}

// connectionTest function (previously blinkTopSection()) makes Connection UI elements flash to indicate Connection status
void MainWindow::connectionTest() {
    ui->log->append("Connection lost. Please try again in a moment."); // report connection loss to control log

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
    setConnectionLock(true); // unlock the UI connection components
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

void MainWindow::addRecordingButtonClicked() {

    string name = ui->nameComboBox->currentText().toStdString();
    int group = selectedGroup;
    int batteryPercent = device->getBattery()->getBatteryLevel();
    int intensity = device->getSessions(group-1, selectedSession-1)->getIntensity();

    if (device->addRecording(name, intensity, group, batteryPercent, connectionIntensity) == -1) {
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



void MainWindow::playReplayButtonClicked() {
    int desiredNum = ui->historySpinBox->value();
    if (desiredNum == 0) { return; }

    string name = ui->nameComboBox->currentText().toStdString();
    Recording* desiredRecording;

    int counter = 0;
    for (int i = 0; i < device->getNumRecordings(); i ++) {
        if (device->getRecordingAt(i)->getName() == name) {
            counter++;
            if (counter == desiredNum) {
                desiredRecording = device->getRecordingAt(i);
            }
        }
    }
    replayRecording(desiredRecording);
}

void MainWindow::replayRecording(Recording *recording) {
    int group = recording->getGroup();
    int intensity = recording->getIntensity();
    int batteryPercent = recording->getBatteryPercent();
    int connection = recording->getConnection();
    int session;

    switch (intensity) {
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
    while (ui->batterySlider->value() != batteryPercent) {
        if (ui->batterySlider->value() < batteryPercent) {
            ui->batterySlider->setValue(ui->batterySlider->value() + 1);
            sleepy(10);
        } else {
            ui->batterySlider->setValue(ui->batterySlider->value() - 1);
            sleepy(10);
        }
    }
    ui_initializeBattery();

    //START THERAPY
    therapy(group, session, 1);
}
