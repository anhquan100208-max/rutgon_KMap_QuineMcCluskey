/********************************************************************************
** Form generated from reading UI file 'mainwindow1.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW1_H
#define UI_MAINWINDOW1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow1
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *btnKarnaugh;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow1)
    {
        if (MainWindow1->objectName().isEmpty())
            MainWindow1->setObjectName("MainWindow1");
        MainWindow1->resize(800, 600);
        centralwidget = new QWidget(MainWindow1);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(200, 70, 421, 61));
        QFont font;
        font.setPointSize(20);
        font.setItalic(true);
        font.setKerning(true);
        label->setFont(font);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        btnKarnaugh = new QPushButton(centralwidget);
        btnKarnaugh->setObjectName("btnKarnaugh");
        btnKarnaugh->setGeometry(QRect(190, 130, 451, 271));
        QFont font1;
        font1.setPointSize(100);
        font1.setBold(true);
        font1.setItalic(true);
        font1.setUnderline(true);
        font1.setStrikeOut(false);
        font1.setKerning(true);
        btnKarnaugh->setFont(font1);
        MainWindow1->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow1);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 36));
        MainWindow1->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow1);
        statusbar->setObjectName("statusbar");
        MainWindow1->setStatusBar(statusbar);

        retranslateUi(MainWindow1);

        QMetaObject::connectSlotsByName(MainWindow1);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow1)
    {
        MainWindow1->setWindowTitle(QCoreApplication::translate("MainWindow1", "MainWindow1", nullptr));
        label->setText(QCoreApplication::translate("MainWindow1", "R\303\272t g\341\273\215n bi\341\273\203u th\341\273\251c logic qu\303\241 l\303\240 d\341\273\205 v\341\273\233i ch\303\272ng t\303\264i", nullptr));
        btnKarnaugh->setText(QCoreApplication::translate("MainWindow1", "B\341\272\257t \304\221\341\272\247u", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow1: public Ui_MainWindow1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW1_H
