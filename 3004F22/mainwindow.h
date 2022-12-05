#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextBrowser>
#include <QElapsedTimer>
#include <QPushButton>
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
        int selectedGroup = 1;
        int connectionIntensity = 1;

        QElapsedTimer blinkTimer;
        QElapsedTimer elapsedTimer;
        QElapsedTimer therapyTimer;

        void changeTextColor(QTextBrowser *text, QColor color);
        void changeBackgroundColor(QPushButton *button, const QString& color, const QString& image);
        void blinkTopSection();
        void blinkBattery();
        void blinkSession(int sessionNum);
        void sleepy(int sleepTime);
        void cycleGroupButton();
        void turnOff();

        void therapy(int groupNum, int sessionNum);
        void drainBattery();
        bool checkBattery();

    private slots:
        void pressPower();
        void powerReleased();
        void pressUpArrow();
        void pressDownArrow();
        void pressSelect();
        void changeConnectionSlider();
        void changeBatterySlider();
        void connectEarClips();
        void disconnectEarClips();
};
#endif // MAINWINDOW_H
