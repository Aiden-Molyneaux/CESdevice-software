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

    //QUICKLY BREAK WHILE LOOP IN blinkTopSection() IF IT IS BLINKING
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
    therapy(selectedGroup, selectedSession);
}

void MainWindow::therapy(int groupNum, int sessionNum){
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

    // Begin session with blinking session icon and 5 second count down
    device->setIsInSession(true);
    ui->log->append("Therapy session will begin in 5 seconds:");
    blinkSession(sessionNum); // make the session icon blink for a couple seconds

    for(int i=5; i>0; i--){
        QString text = "";
        text.append(QString::number(i));
        ui->log->append(text);
        sleepy(100); // small sleep to simulate count down
    }

    int therapyLengthMS = device->getGroups(groupNum-1)->getLengthMS();
//    device->setCurrentIntensity(device->getSessions(groupNum-1, sessionNum-1)->getIntensity());
//    int sessionIntensity = device->getCurrentIntensity();

    therapyTimer.start(); // Timer tracks elapsed time
    while(therapyTimer.elapsed() < therapyLengthMS){
        // Check that Battery levels are sufficient - if not, end the session early
        if(!checkBattery()){
            ui->log->append("Battery level too low. Replace Batteries");
            ui->log->append("Session will now end early. Device will now power down via Soft Off protocol.");
            return;
        }

        // Check that connection strength is sufficient - if not pause the session
        // PROBLEM AREA - if you press "Disconnect Earclips" while session is running, session will quit, but it won't enter this conditional
        // additionally, connectionIntensity is set to 1, but this cout will say that it's still 3 (which is why it doesn't enter the loop)

        cout << "Connection: " << connectionIntensity << endl;
        if(connectionIntensity==1){
            cout << "Hello" << endl;
            ui->log->append("Connection level is poor. Please adjust.");
            sleepy(4000);
            return;
        }

        drainBattery();
        sleepy(150);
        cout << device->getBattery()->getBatteryLevel() << endl;
    }
}

void MainWindow::drainBattery(){
    device->getBattery()->setBatteryLevel(device->getBattery()->getBatteryLevel()-1);
    ui->batterySlider->setValue(device->getBattery()->getBatteryLevel());
    ui_initializeBattery();
}

bool MainWindow::checkBattery(){
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

            blinkTopSection();
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

void MainWindow::blinkTopSection() {
    while (connectionIntensity == 1) {
        changeTextColor(ui->connectionTop, "red");
        sleepy(100);
        changeTextColor(ui->connectionTop, "gray");
        sleepy(100);
    }
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

