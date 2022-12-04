#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    device = new Device("TimeToLive");
    connect(ui->powerButton, SIGNAL(pressed()), this, SLOT (pressPower()));
    connect(ui->powerButton, SIGNAL(released()), this, SLOT (powerReleased()));
    connect(ui->upArrowButton, SIGNAL(released()), this, SLOT (pressUpArrow()));
    connect(ui->downArrowButton, SIGNAL(released()), this, SLOT (pressDownArrow()));
    connect(ui->connectionSlider, SIGNAL(sliderReleased()), this, SLOT (changeConnectionSlider()));
}

MainWindow::~MainWindow() {
    delete ui;
    delete device;
}

void MainWindow::powerReleased(){
    if(elapsedTimer.elapsed()>=2000){ // check if Power Button was held for 2 seconds
        if(!device->getIsPoweredOn()){ // continue if DEVICE is OFF
            ui_initializeBattery();
            if(device->getBattery()->getBatteryLevel()<33){
                ui->log->append("Battery level too low. Replace Batteries");
                // implement battery blinking
                return;
            }
            ui->deltaButton->setStyleSheet("QPushButton {border-image: url(:/icons/delta.png); background-color: green; border-radius: 40;}");
        }else{ // continue if DEVICE is ON

        }
        cout << "Do something" << endl;


        device->getPowerButton()->pressed();
        changeConnectionSlider();
    }else{
        cout << "Do something else" << endl;
    }
}

void MainWindow::pressPower(){
    elapsedTimer.start();
}

void MainWindow::pressUpArrow(){
    if (!device->getIsPoweredOn()) {return;}

    device->getUpArrowButton()->pressed();

    switch (selectedSession) {
        //DELTA IS LIT UP, WE WANT THETA LIT INSTEAD
        case 1:
            ui->deltaButton->setStyleSheet("QPushButton {border-image: url(:/icons/delta.png); background-color: white; border-radius: 40;}");
            ui->thetaButton->setStyleSheet("QPushButton {border-image: url(:/icons/theta.png); background-color: green; border-radius: 40;}");
            selectedSession++;
        break;
        //THETA IS LIT UP, WE WANT ALPHA LIT INSTEAD
        case 2:
            ui->thetaButton->setStyleSheet("QPushButton {border-image: url(:/icons/theta.png); background-color: white; border-radius: 40;}");
            ui->alphaButton->setStyleSheet("QPushButton {border-image: url(:/icons/alpha.png); background-color: green; border-radius: 40;}");
            selectedSession++;
        break;
        //ALPHA IS LIT UP, WE WANT BETA LIT INSTEAD
        case 3:
            ui->alphaButton->setStyleSheet("QPushButton {border-image: url(:/icons/alpha.png); background-color: white; border-radius: 40;}");
            ui->betaButton->setStyleSheet("QPushButton {border-image: url(:/icons/beta.png); background-color: green; border-radius: 40;}");
            selectedSession++;
        break;
        //BETA IS LIT UP, WE WANT DELTA LIT INSTEAD
        case 4:
            ui->betaButton->setStyleSheet("QPushButton {border-image: url(:/icons/beta.png); background-color: white; border-radius: 40;}");
            ui->deltaButton->setStyleSheet("QPushButton {border-image: url(:/icons/delta.png); background-color: green; border-radius: 40;}");
            selectedSession = 1;
        break;
    }
}

void MainWindow::pressDownArrow(){
    if (!device->getIsPoweredOn()) {return;}

    device->getDownArrowButton()->pressed();

    switch (selectedSession) {
        //DELTA IS LIT UP, WE WANT BETA LIT INSTEAD
        case 1:
            ui->deltaButton->setStyleSheet("QPushButton {border-image: url(:/icons/delta.png); background-color: white; border-radius: 40;}");
            ui->betaButton->setStyleSheet("QPushButton {border-image: url(:/icons/beta.png); background-color: green; border-radius: 40;}");
            selectedSession = 4;
        break;
        //THETA IS LIT UP, WE WANT DELTA LIT INSTEAD
        case 2:
            ui->thetaButton->setStyleSheet("QPushButton {border-image: url(:/icons/theta.png); background-color: white; border-radius: 40;}");
            ui->deltaButton->setStyleSheet("QPushButton {border-image: url(:/icons/delta.png); background-color: green; border-radius: 40;}");
            selectedSession--;
        break;
        //ALPHA IS LIT UP, WE WANT THETA LIT INSTEAD
        case 3:
            ui->alphaButton->setStyleSheet("QPushButton {border-image: url(:/icons/alpha.png); background-color: white; border-radius: 40;}");
            ui->thetaButton->setStyleSheet("QPushButton {border-image: url(:/icons/theta.png); background-color: green; border-radius: 40;}");
            selectedSession--;
        break;
        //BETA IS LIT UP, WE WANT APLHA LIT INSTEAD
        case 4:
            ui->betaButton->setStyleSheet("QPushButton {border-image: url(:/icons/beta.png); background-color: white; border-radius: 40;}");
            ui->alphaButton->setStyleSheet("QPushButton {border-image: url(:/icons/alpha.png); background-color: green; border-radius: 40;}");
            selectedSession--;
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
void MainWindow::ui_initializeBattery(){
    ui->batteryLevel1->setStyleSheet("QTextBrowser {background-color: red;}");
    if(device->getBattery()->getBatteryLevel()>=33){
        ui->batteryLevel2->setStyleSheet("QTextBrowser {background-color: yellow;}");
        if(device->getBattery()->getBatteryLevel()>=67){
                ui->batteryLevel3->setStyleSheet("QTextBrowser {background-color: green;}");
        }
    }
}

void MainWindow::sleepy(int sleepTime) {
    QTime dieTime = QTime::currentTime().addMSecs(sleepTime);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

