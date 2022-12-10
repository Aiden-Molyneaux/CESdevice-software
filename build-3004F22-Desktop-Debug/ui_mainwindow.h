/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *powerButton;
    QPushButton *downArrowButton;
    QPushButton *upArrowButton;
    QPushButton *checkButton;
    QTextBrowser *connectionBottom;
    QTextBrowser *connectionMiddle;
    QTextBrowser *connectionTop;
    QPushButton *alphaButton;
    QPushButton *deltaButton;
    QPushButton *betaButton;
    QPushButton *thetaButton;
    QPushButton *group20Button;
    QPushButton *group45Button;
    QPushButton *groupUserButton;
    QGroupBox *groupBox;
    QPushButton *CESButton;
    QGroupBox *groupBox_4;
    QTextBrowser *batteryLevel1;
    QTextBrowser *batteryLevel2;
    QTextBrowser *batteryLevel3;
    QPushButton *CES2Button;
    QPushButton *stopButton;
    QLabel *graphLabel;
    QTextEdit *powerLight;
    QGroupBox *groupBox_2;
    QTextBrowser *log;
    QLabel *label_3;
    QGroupBox *groupBox_3;
    QPushButton *addUserButton;
    QPlainTextEdit *userNameInput;
    QLabel *label_4;
    QPlainTextEdit *userDurationInput;
    QLabel *label_5;
    QComboBox *nameComboBox;
    QPushButton *printHistoryButton;
    QSpinBox *historySpinBox;
    QPushButton *playReplayButton;
    QGroupBox *groupBox_5;
    QTextBrowser *currentIntensityLog;
    QLabel *label_6;
    QSlider *batterySlider;
    QLabel *label_2;
    QSlider *connectionSlider;
    QLabel *label;
    QPushButton *connectEarclipsButton;
    QPushButton *disconnectEarclipsButton;
    QGroupBox *groupBox_6;
    QTextBrowser *testLog;
    QLabel *label_7;
    QPushButton *testAddUser;
    QPushButton *testAddBadUser;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1830, 590);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        powerButton = new QPushButton(centralwidget);
        powerButton->setObjectName(QString::fromUtf8("powerButton"));
        powerButton->setGeometry(QRect(560, 440, 101, 71));
        powerButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icons/power.png);\n"
"	color: white;\n"
"}"));
        powerButton->setAutoRepeat(false);
        powerButton->setAutoRepeatDelay(200);
        downArrowButton = new QPushButton(centralwidget);
        downArrowButton->setObjectName(QString::fromUtf8("downArrowButton"));
        downArrowButton->setGeometry(QRect(430, 440, 101, 71));
        downArrowButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icons/down.png);\n"
"	color: white;\n"
"}"));
        upArrowButton = new QPushButton(centralwidget);
        upArrowButton->setObjectName(QString::fromUtf8("upArrowButton"));
        upArrowButton->setGeometry(QRect(430, 350, 101, 71));
        upArrowButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icons/up.png);\n"
"	color: white;\n"
"}"));
        checkButton = new QPushButton(centralwidget);
        checkButton->setObjectName(QString::fromUtf8("checkButton"));
        checkButton->setGeometry(QRect(80, 440, 101, 71));
        checkButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icons/check.png);\n"
"	color: white;\n"
"}"));
        connectionBottom = new QTextBrowser(centralwidget);
        connectionBottom->setObjectName(QString::fromUtf8("connectionBottom"));
        connectionBottom->setGeometry(QRect(270, 430, 51, 121));
        connectionMiddle = new QTextBrowser(centralwidget);
        connectionMiddle->setObjectName(QString::fromUtf8("connectionMiddle"));
        connectionMiddle->setGeometry(QRect(270, 310, 51, 121));
        connectionMiddle->setStyleSheet(QString::fromUtf8(""));
        connectionTop = new QTextBrowser(centralwidget);
        connectionTop->setObjectName(QString::fromUtf8("connectionTop"));
        connectionTop->setGeometry(QRect(270, 230, 51, 81));
        alphaButton = new QPushButton(centralwidget);
        alphaButton->setObjectName(QString::fromUtf8("alphaButton"));
        alphaButton->setGeometry(QRect(320, 120, 81, 81));
        alphaButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icons/alpha.png);\n"
"	background-color: white;\n"
"	border-radius: 40;\n"
"}"));
        alphaButton->setCheckable(false);
        deltaButton = new QPushButton(centralwidget);
        deltaButton->setObjectName(QString::fromUtf8("deltaButton"));
        deltaButton->setGeometry(QRect(100, 120, 81, 81));
        deltaButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icons/delta.png);\n"
"	background-color: white;\n"
"	border-radius: 40;\n"
"}"));
        deltaButton->setCheckable(false);
        betaButton = new QPushButton(centralwidget);
        betaButton->setObjectName(QString::fromUtf8("betaButton"));
        betaButton->setGeometry(QRect(440, 120, 81, 81));
        betaButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icons/beta.png);\n"
"	background-color: white;\n"
"	border-radius: 40;\n"
"}"));
        betaButton->setCheckable(false);
        thetaButton = new QPushButton(centralwidget);
        thetaButton->setObjectName(QString::fromUtf8("thetaButton"));
        thetaButton->setGeometry(QRect(210, 120, 81, 81));
        thetaButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icons/theta.png);\n"
"	background-color: white;\n"
"	border-radius: 40;\n"
"}"));
        thetaButton->setCheckable(false);
        group20Button = new QPushButton(centralwidget);
        group20Button->setObjectName(QString::fromUtf8("group20Button"));
        group20Button->setGeometry(QRect(170, 20, 81, 81));
        group20Button->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icons/20.png);\n"
"	background-color: white;\n"
"	border-radius: 40;\n"
"}"));
        group20Button->setCheckable(false);
        group45Button = new QPushButton(centralwidget);
        group45Button->setObjectName(QString::fromUtf8("group45Button"));
        group45Button->setGeometry(QRect(290, 20, 81, 81));
        group45Button->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icons/45.png);\n"
"	background-color: white;\n"
"	border-radius: 40;\n"
"}"));
        group45Button->setCheckable(false);
        groupUserButton = new QPushButton(centralwidget);
        groupUserButton->setObjectName(QString::fromUtf8("groupUserButton"));
        groupUserButton->setGeometry(QRect(400, 20, 81, 81));
        groupUserButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icons/user.png);\n"
"	background-color: white;\n"
"	border-radius: 40;\n"
"}"));
        groupUserButton->setCheckable(false);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, -20, 761, 571));
        CESButton = new QPushButton(groupBox);
        CESButton->setObjectName(QString::fromUtf8("CESButton"));
        CESButton->setGeometry(QRect(510, 50, 71, 71));
        CESButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icons/CES.png);\n"
"	background-color: white;\n"
"	border-radius: 34;\n"
"}"));
        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(680, 40, 71, 141));
        batteryLevel1 = new QTextBrowser(groupBox_4);
        batteryLevel1->setObjectName(QString::fromUtf8("batteryLevel1"));
        batteryLevel1->setGeometry(QRect(20, 100, 31, 31));
        batteryLevel2 = new QTextBrowser(groupBox_4);
        batteryLevel2->setObjectName(QString::fromUtf8("batteryLevel2"));
        batteryLevel2->setGeometry(QRect(20, 70, 31, 31));
        batteryLevel3 = new QTextBrowser(groupBox_4);
        batteryLevel3->setObjectName(QString::fromUtf8("batteryLevel3"));
        batteryLevel3->setGeometry(QRect(20, 40, 31, 31));
        CES2Button = new QPushButton(groupBox);
        CES2Button->setObjectName(QString::fromUtf8("CES2Button"));
        CES2Button->setGeometry(QRect(590, 50, 71, 71));
        CES2Button->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icons/CES2.png);\n"
"	background-color: white;\n"
"	border-radius: 35;\n"
"}"));
        stopButton = new QPushButton(groupBox);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));
        stopButton->setEnabled(true);
        stopButton->setGeometry(QRect(190, 500, 41, 41));
        stopButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icons/stop.png);\n"
"	background-color: white;\n"
"	border-radius: 20;\n"
"}"));
        graphLabel = new QLabel(groupBox);
        graphLabel->setObjectName(QString::fromUtf8("graphLabel"));
        graphLabel->setGeometry(QRect(180, 230, 181, 17));
        powerLight = new QTextEdit(groupBox);
        powerLight->setObjectName(QString::fromUtf8("powerLight"));
        powerLight->setGeometry(QRect(570, 430, 41, 21));
        powerLight->setStyleSheet(QString::fromUtf8(""));
        powerLight->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(790, -20, 671, 571));
        log = new QTextBrowser(groupBox_2);
        log->setObjectName(QString::fromUtf8("log"));
        log->setGeometry(QRect(20, 70, 641, 291));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(280, 50, 101, 20));
        groupBox_3 = new QGroupBox(groupBox_2);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(400, 370, 261, 191));
        addUserButton = new QPushButton(groupBox_3);
        addUserButton->setObjectName(QString::fromUtf8("addUserButton"));
        addUserButton->setGeometry(QRect(100, 80, 80, 25));
        userNameInput = new QPlainTextEdit(groupBox_3);
        userNameInput->setObjectName(QString::fromUtf8("userNameInput"));
        userNameInput->setGeometry(QRect(30, 40, 104, 31));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(60, 20, 54, 17));
        userDurationInput = new QPlainTextEdit(groupBox_3);
        userDurationInput->setObjectName(QString::fromUtf8("userDurationInput"));
        userDurationInput->setGeometry(QRect(140, 40, 104, 31));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(140, 20, 111, 17));
        nameComboBox = new QComboBox(groupBox_3);
        nameComboBox->setObjectName(QString::fromUtf8("nameComboBox"));
        nameComboBox->setGeometry(QRect(60, 120, 72, 25));
        printHistoryButton = new QPushButton(groupBox_3);
        printHistoryButton->setObjectName(QString::fromUtf8("printHistoryButton"));
        printHistoryButton->setGeometry(QRect(140, 120, 80, 25));
        historySpinBox = new QSpinBox(groupBox_3);
        historySpinBox->setObjectName(QString::fromUtf8("historySpinBox"));
        historySpinBox->setGeometry(QRect(64, 150, 71, 26));
        historySpinBox->setMaximum(0);
        playReplayButton = new QPushButton(groupBox_3);
        playReplayButton->setObjectName(QString::fromUtf8("playReplayButton"));
        playReplayButton->setGeometry(QRect(140, 150, 80, 25));
        groupBox_5 = new QGroupBox(groupBox_2);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(29, 369, 351, 191));
        currentIntensityLog = new QTextBrowser(groupBox_5);
        currentIntensityLog->setObjectName(QString::fromUtf8("currentIntensityLog"));
        currentIntensityLog->setGeometry(QRect(80, 160, 61, 21));
        currentIntensityLog->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        label_6 = new QLabel(groupBox_5);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(60, 140, 101, 17));
        batterySlider = new QSlider(groupBox_5);
        batterySlider->setObjectName(QString::fromUtf8("batterySlider"));
        batterySlider->setGeometry(QRect(30, 120, 160, 16));
        batterySlider->setMinimum(0);
        batterySlider->setMaximum(100);
        batterySlider->setValue(100);
        batterySlider->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(groupBox_5);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(70, 90, 81, 20));
        connectionSlider = new QSlider(groupBox_5);
        connectionSlider->setObjectName(QString::fromUtf8("connectionSlider"));
        connectionSlider->setEnabled(false);
        connectionSlider->setGeometry(QRect(30, 70, 160, 16));
        connectionSlider->setMinimum(1);
        connectionSlider->setMaximum(3);
        connectionSlider->setOrientation(Qt::Horizontal);
        label = new QLabel(groupBox_5);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 40, 81, 20));
        connectEarclipsButton = new QPushButton(groupBox_5);
        connectEarclipsButton->setObjectName(QString::fromUtf8("connectEarclipsButton"));
        connectEarclipsButton->setGeometry(QRect(210, 70, 121, 25));
        disconnectEarclipsButton = new QPushButton(groupBox_5);
        disconnectEarclipsButton->setObjectName(QString::fromUtf8("disconnectEarclipsButton"));
        disconnectEarclipsButton->setGeometry(QRect(210, 120, 121, 25));
        groupBox_5->raise();
        log->raise();
        label_3->raise();
        groupBox_3->raise();
        groupBox_6 = new QGroupBox(centralwidget);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(1470, -20, 341, 571));
        testLog = new QTextBrowser(groupBox_6);
        testLog->setObjectName(QString::fromUtf8("testLog"));
        testLog->setGeometry(QRect(10, 70, 321, 291));
        label_7 = new QLabel(groupBox_6);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(100, 50, 141, 17));
        testAddUser = new QPushButton(groupBox_6);
        testAddUser->setObjectName(QString::fromUtf8("testAddUser"));
        testAddUser->setGeometry(QRect(20, 380, 80, 25));
        testAddBadUser = new QPushButton(groupBox_6);
        testAddBadUser->setObjectName(QString::fromUtf8("testAddBadUser"));
        testAddBadUser->setGeometry(QRect(110, 380, 91, 25));
        MainWindow->setCentralWidget(centralwidget);
        groupBox->raise();
        group45Button->raise();
        groupUserButton->raise();
        powerButton->raise();
        downArrowButton->raise();
        upArrowButton->raise();
        checkButton->raise();
        connectionBottom->raise();
        connectionMiddle->raise();
        connectionTop->raise();
        alphaButton->raise();
        deltaButton->raise();
        betaButton->raise();
        thetaButton->raise();
        group20Button->raise();
        groupBox_2->raise();
        groupBox_6->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1830, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        powerButton->setText(QString());
        downArrowButton->setText(QString());
        upArrowButton->setText(QString());
        checkButton->setText(QString());
        connectionBottom->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Noto Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; color:#888a85;\">|3|</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; color:#888a85;\">|2|</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; color:#888a85;\">|1|</span></p></body></html>", nullptr));
        connectionMiddle->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Noto Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; color:#888a85;\">|6|</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; color:#888a85;\">|5|</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; color:#888a85;\">|4|</span></p></body></html>", nullptr));
        connectionTop->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Noto Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; color:#888a85;\">|8|</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; color:#888a85;\">|7|</span></p></body></html>", nullptr));
        alphaButton->setText(QString());
        deltaButton->setText(QString());
        betaButton->setText(QString());
        thetaButton->setText(QString());
        group20Button->setText(QString());
        group45Button->setText(QString());
        groupUserButton->setText(QString());
        groupBox->setTitle(QApplication::translate("MainWindow", "GroupBox", nullptr));
        CESButton->setText(QString());
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Battery", nullptr));
        CES2Button->setText(QString());
        stopButton->setText(QString());
        graphLabel->setText(QApplication::translate("MainWindow", "Currently indicating: ", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "GroupBox", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Output Console", nullptr));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "User Add and Replay History ", nullptr));
        addUserButton->setText(QApplication::translate("MainWindow", "Add User", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Name", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Duration (minutes)", nullptr));
        printHistoryButton->setText(QApplication::translate("MainWindow", "Print history", nullptr));
        playReplayButton->setText(QApplication::translate("MainWindow", "Play replay", nullptr));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Connection, Battery Level and Intensity", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Current Intensity", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Battery Level", nullptr));
        label->setText(QApplication::translate("MainWindow", "Connection", nullptr));
        connectEarclipsButton->setText(QApplication::translate("MainWindow", "Connect Earclips", nullptr));
        disconnectEarclipsButton->setText(QApplication::translate("MainWindow", "Disconnect Earclips", nullptr));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "GroupBox", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "Testing Output Console", nullptr));
        testAddUser->setText(QApplication::translate("MainWindow", "Add A User", nullptr));
        testAddBadUser->setText(QApplication::translate("MainWindow", "Add Bad User", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
