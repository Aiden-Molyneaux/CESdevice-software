#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    device = new Device("TimeToLive");

    connect(ui->powerButton, SIGNAL(released()), this, SLOT (pressPower()));
    connect(ui->upArrowButton, SIGNAL(released()), this, SLOT (pressUpArrow()));

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
}



