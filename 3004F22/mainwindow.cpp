#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    device = new Device("TimeToLive");

    connect(ui->powerButton, SIGNAL(released()), this, SLOT (pressPower()));
    connect(ui->upArrowButton, SIGNAL(released()), this, SLOT (pressUpArrow()));
    connect(ui->downArrowButton, SIGNAL(released()), this, SLOT (pressDownArrow()));
}

MainWindow::~MainWindow() {
    delete ui;
    delete device;
}

void MainWindow::pressPower(){
    device->getPowerButton()->pressed();
}

void MainWindow::pressUpArrow(){
    device->getUpArrowButton()->pressed();

    switch (selectedSession) {
        //DELTA IS LIT UP, WE WANT THETA LIT INSTEAD
        case 1:
            cout << "WE IN HERE" << endl;
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



