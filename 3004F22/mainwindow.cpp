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
}

MainWindow::~MainWindow() {
    delete ui;
    delete device;
}

void MainWindow::powerReleased(){
    if(elapsedTimer.elapsed()>=200){ // check if Power Button was held for 2 seconds
        if(!device->getIsPoweredOn()){ // continue if DEVICE is OFF
            ui_initializeBattery();
            if(device->getBattery()->getBatteryLevel()<33){
                ui->log->append("Battery level too low. Replace Batteries");
                blinkBattery();
                return;
            }
            changeBackgroundColor(ui->deltaButton, "green", "delta");
            changeBackgroundColor(ui->group20Button, "green", "20");
        }else{ // continue if DEVICE is ON

        }

        device->getPowerButton()->pressed();
        changeConnectionSlider();
    }else{
        cycleGroupButton();
    }
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
    while (device->getBattery()->getBatteryLevel()<33) {
        ui->batteryLevel1->setStyleSheet("QTextBrowser {background-color: white;}");
        sleepy(100);
        ui->batteryLevel1->setStyleSheet("QTextBrowser {background-color: red;}");
        sleepy(100);
    }
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

