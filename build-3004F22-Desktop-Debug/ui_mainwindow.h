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
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
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
    QGroupBox *groupBox_2;
    QTextBrowser *log;
    QLabel *label_3;
    QSlider *connectionSlider;
    QLabel *label;
    QSlider *batterySlider;
    QLabel *label_2;
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
    QPushButton *addFakeRecordingButton;
    QRadioButton *recordSessionRadioButton;
    QPushButton *connectEarclipsButton;
    QPushButton *disconnectEarclipsButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1599, 590);
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
        groupBox->setGeometry(QRect(20, -20, 781, 581));
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
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(820, -20, 771, 571));
        log = new QTextBrowser(groupBox_2);
        log->setObjectName(QString::fromUtf8("log"));
        log->setGeometry(QRect(10, 70, 256, 291));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(100, 50, 81, 20));
        connectionSlider = new QSlider(groupBox_2);
        connectionSlider->setObjectName(QString::fromUtf8("connectionSlider"));
        connectionSlider->setEnabled(false);
        connectionSlider->setGeometry(QRect(60, 410, 160, 16));
        connectionSlider->setMinimum(1);
        connectionSlider->setMaximum(3);
        connectionSlider->setOrientation(Qt::Horizontal);
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(100, 390, 81, 20));
        batterySlider = new QSlider(groupBox_2);
        batterySlider->setObjectName(QString::fromUtf8("batterySlider"));
        batterySlider->setGeometry(QRect(60, 460, 160, 16));
        batterySlider->setMinimum(0);
        batterySlider->setMaximum(100);
        batterySlider->setValue(100);
        batterySlider->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(90, 440, 81, 20));
        groupBox_3 = new QGroupBox(groupBox_2);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(280, 70, 441, 191));
        addUserButton = new QPushButton(groupBox_3);
        addUserButton->setObjectName(QString::fromUtf8("addUserButton"));
        addUserButton->setGeometry(QRect(90, 90, 80, 25));
        userNameInput = new QPlainTextEdit(groupBox_3);
        userNameInput->setObjectName(QString::fromUtf8("userNameInput"));
        userNameInput->setGeometry(QRect(30, 40, 104, 41));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(60, 20, 54, 17));
        userDurationInput = new QPlainTextEdit(groupBox_3);
        userDurationInput->setObjectName(QString::fromUtf8("userDurationInput"));
        userDurationInput->setGeometry(QRect(140, 40, 104, 41));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(160, 20, 54, 17));
        nameComboBox = new QComboBox(groupBox_3);
        nameComboBox->setObjectName(QString::fromUtf8("nameComboBox"));
        nameComboBox->setGeometry(QRect(280, 40, 72, 25));
        printHistoryButton = new QPushButton(groupBox_3);
        printHistoryButton->setObjectName(QString::fromUtf8("printHistoryButton"));
        printHistoryButton->setGeometry(QRect(350, 40, 80, 25));
        historySpinBox = new QSpinBox(groupBox_3);
        historySpinBox->setObjectName(QString::fromUtf8("historySpinBox"));
        historySpinBox->setGeometry(QRect(290, 80, 45, 26));
        playReplayButton = new QPushButton(groupBox_3);
        playReplayButton->setObjectName(QString::fromUtf8("playReplayButton"));
        playReplayButton->setGeometry(QRect(350, 80, 80, 25));
        addFakeRecordingButton = new QPushButton(groupBox_3);
        addFakeRecordingButton->setObjectName(QString::fromUtf8("addFakeRecordingButton"));
        addFakeRecordingButton->setGeometry(QRect(279, 140, 111, 25));
        recordSessionRadioButton = new QRadioButton(groupBox_3);
        recordSessionRadioButton->setObjectName(QString::fromUtf8("recordSessionRadioButton"));
        recordSessionRadioButton->setGeometry(QRect(50, 140, 131, 23));
        connectEarclipsButton = new QPushButton(groupBox_2);
        connectEarclipsButton->setObjectName(QString::fromUtf8("connectEarclipsButton"));
        connectEarclipsButton->setGeometry(QRect(280, 280, 121, 25));
        disconnectEarclipsButton = new QPushButton(groupBox_2);
        disconnectEarclipsButton->setObjectName(QString::fromUtf8("disconnectEarclipsButton"));
        disconnectEarclipsButton->setGeometry(QRect(280, 310, 121, 25));
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
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1599, 22));
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
        groupBox_2->setTitle(QApplication::translate("MainWindow", "GroupBox", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "CONSOLE", nullptr));
        label->setText(QApplication::translate("MainWindow", "CONNECTION", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Battery Level", nullptr));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "USER STUFF", nullptr));
        addUserButton->setText(QApplication::translate("MainWindow", "Add User", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Name", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Duration", nullptr));
        printHistoryButton->setText(QApplication::translate("MainWindow", "Print history", nullptr));
        playReplayButton->setText(QApplication::translate("MainWindow", "Play replay", nullptr));
        addFakeRecordingButton->setText(QApplication::translate("MainWindow", "add fake recording", nullptr));
        recordSessionRadioButton->setText(QApplication::translate("MainWindow", "Record next session", nullptr));
        connectEarclipsButton->setText(QApplication::translate("MainWindow", "Connect Earclips", nullptr));
        disconnectEarclipsButton->setText(QApplication::translate("MainWindow", "Disconnect Earclips", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
