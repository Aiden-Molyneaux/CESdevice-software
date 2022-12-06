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

        void ui_initializeBattery();
        void ui_turnOffBattery();

    private:
        Ui::MainWindow *ui;
        Device* device;

        int selectedSession = 1;
        int selectedGroup = 1;
        int connectionIntensity = 1;
        int timesIntensityAdjusted;

        QElapsedTimer blinkTimer;
        QElapsedTimer elapsedTimer;
        QElapsedTimer selectTimer;
        QElapsedTimer pauseTimer;
        QElapsedTimer therapyTimer;
        QElapsedTimer timeoutTimer;

        void changeTextColor(QTextBrowser *text, QColor color);
        void changeBackgroundColor(QPushButton *button, const QString& color, const QString& image, const QString& radius = "40");
        void connectionTest(); // formally blinkTopSection()
        void bootConnectionTest();
        void blinkBattery();
        void blinkSession(int sessionNum);
        void sleepy(int sleepTime);
        void cycleGroupButton();
        void turnOff();

        void therapy(int groupNum, int sessionNum, int recordingFlag = 0);
        void replayRecording(Recording* recording);
        void addRecording(const string& name, int group, int batteryPercent, int initialIntensity, int intensity = -1);
        void drainBattery(int intensity);
        bool checkBattery();
        void batteryWarning();
        void setConnectionLock(bool status);

        void updateIntensityLog();
        void displayIntensityOnGraph();
        void displayIntensityWarning(int flag);

    private slots:
        void pressPower();
        void powerReleased();
        void pressUpArrow();
        void pressDownArrow();
        void pressSelect();
        void releaseSelect();
        void changeConnectionSlider();
        void changeBatterySlider();
        void connectEarClips();
        void disconnectEarClips();
        void addUserButtonClicked();
        void printHistoryButtonClicked();
        void playReplayButtonClicked();
        void stopPressed();
};
#endif // MAINWINDOW_H
