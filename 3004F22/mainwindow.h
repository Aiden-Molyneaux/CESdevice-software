#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextBrowser>
#include <QElapsedTimer>
#include <QPushButton>
#include <QTime>
#include <cmath>
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

        bool flag = false;

    private:
        Ui::MainWindow *ui;
        Device* device;

        int selectedSession = 1;
        int selectedGroup = 1;
        int connectionIntensity = 1;
        int timesIntensityAdjusted;
        bool endSessionEarlyFlag;

        QElapsedTimer blinkTimer;
        QElapsedTimer powerPressedTimer;
        QElapsedTimer selectTimer;
        QElapsedTimer pauseTimer;
        QElapsedTimer therapyTimer;
        QElapsedTimer timeoutTimer;

        // MAIN FUNCTIONS
        void therapy(int groupNum, int sessionNum, int recordingFlag = 0, int overrideIntensity = -1);
        void connectionTest();
        void addRecording(const string& name, int group, int batteryPercent, int initialIntensity, int intensity = -1);
        void replayRecording(Recording* recording);

        // HELPER FUNCTIONS
        void changeTextColor(QTextBrowser *text, QColor color);
        void changeBackgroundColor(QPushButton *button, const QString& color, const QString& image, const QString& radius = "40");
        void bootConnectionTest();
        void blinkSession(int sessionNum);
        void cycleGroupButton();
        void turnOffUI();
        void softOff();
        void setTherapyLock(bool status);
        void updateIntensityLog();
        void displayIntensityOnGraph();
        void powerLightOnOff(bool status);
        void endSessionEarly();

        void ui_initializeBattery();
        void ui_turnOffBattery();

        // Battery functions
        void blinkBattery();
        void drainBattery(int intensity);
        bool checkBattery();
        void batteryWarning();

        void sleepy(int sleepTime);

    private slots:
        // DEVICE UI SLOTS
        void pressPower();
        void powerReleased();
        void pressUpArrow();
        void pressDownArrow();
        void pressSelect();
        void releaseSelect();
        void stopPressed();

        // CONTROL PANEL UI SLOTS
        void connectEarClips();
        void disconnectEarClips();
        void addUserButtonClicked();
        void printHistoryButtonClicked();
        void playReplayButtonClicked();
        void changeConnectionSlider();
        void changeBatterySlider();
};
#endif // MAINWINDOW_H
