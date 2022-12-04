#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    device = new Device("TimeToLive");

    connect(ui->powerButton, SIGNAL(released()), this, SLOT (pressPower()));

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::pressPower(){
    device->getPowerButton()->pressed();
}

