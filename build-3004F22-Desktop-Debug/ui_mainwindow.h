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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *powerButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *checkButton;
    QTextBrowser *connectionBottom;
    QTextBrowser *connectionMiddle;
    QTextBrowser *connectionTop;
    QPushButton *pushButton;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        powerButton = new QPushButton(centralwidget);
        powerButton->setObjectName(QString::fromUtf8("powerButton"));
        powerButton->setGeometry(QRect(560, 440, 101, 71));
        powerButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icons/power.png);\n"
"	color: white;\n"
"}"));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(430, 440, 101, 71));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icons/down.png);\n"
"	color: white;\n"
"}"));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(430, 350, 101, 71));
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        connectionTop = new QTextBrowser(centralwidget);
        connectionTop->setObjectName(QString::fromUtf8("connectionTop"));
        connectionTop->setGeometry(QRect(270, 230, 51, 81));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(320, 120, 81, 81));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icons/alpha.png);\n"
"	background-color: white;\n"
"	border-radius: 40;\n"
"}"));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(100, 120, 81, 81));
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icons/delta.png);\n"
"	background-color: white;\n"
"	border-radius: 40;\n"
"}"));
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(440, 120, 81, 81));
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icons/beta.png);\n"
"	background-color: white;\n"
"	border-radius: 40;\n"
"}"));
        pushButton_6 = new QPushButton(centralwidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(210, 120, 81, 81));
        pushButton_6->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icons/theta.png);\n"
"	background-color: white;\n"
"	border-radius: 40;\n"
"}"));
        pushButton_7 = new QPushButton(centralwidget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(170, 20, 81, 81));
        pushButton_7->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icons/20.png);\n"
"	background-color: white;\n"
"	border-radius: 40;\n"
"}"));
        pushButton_8 = new QPushButton(centralwidget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(290, 20, 81, 81));
        pushButton_8->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icons/45.png);\n"
"	background-color: white;\n"
"	border-radius: 40;\n"
"}"));
        pushButton_9 = new QPushButton(centralwidget);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(400, 20, 81, 81));
        pushButton_9->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icons/user.png);\n"
"	background-color: white;\n"
"	border-radius: 40;\n"
"}"));
        pushButton_10 = new QPushButton(centralwidget);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setGeometry(QRect(630, 30, 81, 81));
        pushButton_10->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icons/CES.png);\n"
"	background-color: white;\n"
"	border-radius: 40;\n"
"}"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
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
        pushButton_2->setText(QString());
        pushButton_3->setText(QString());
        checkButton->setText(QString());
        connectionBottom->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Noto Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; color:#73d216;\">|3|</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; color:#73d216;\">|2|</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; color:#73d216;\">|1|</span></p></body></html>", nullptr));
        connectionMiddle->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Noto Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; color:#f57900;\">|6|</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; color:#f57900;\">|5|</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; color:#f57900;\">|4|</span></p></body></html>", nullptr));
        connectionTop->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Noto Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; color:#ef2929;\">|8|</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; color:#ef2929;\">|7|</span></p></body></html>", nullptr));
        pushButton->setText(QString());
        pushButton_4->setText(QString());
        pushButton_5->setText(QString());
        pushButton_6->setText(QString());
        pushButton_7->setText(QString());
        pushButton_8->setText(QString());
        pushButton_9->setText(QString());
        pushButton_10->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
