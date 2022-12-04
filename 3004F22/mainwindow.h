#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextBrowser>
#include <QElapsedTimer>
#include <QTime>
#include "Device.h"
#include <string>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        void ui_initializeBattery();
        void ui_turnOffBattery();

    private:
        Ui::MainWindow *ui;
        Device* device;

        int selectedSession = 1;
        int connectionIntensity = 1;

        QElapsedTimer blinkTimer;

        void changeTextColor(QTextBrowser *text, QColor color);
        void blinkTopSection();
        void sleepy(int sleepTime);
        QElapsedTimer elapsedTimer;

    private slots:
        void pressPower();
        void powerReleased();
        void pressUpArrow();
        void pressDownArrow();
        void changeConnectionSlider();
};
#endif // MAINWINDOW_H
