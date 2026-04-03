/********************************************************************************
** Form generated from reading UI file 'karnaughwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KARNAUGHWINDOW_H
#define UI_KARNAUGHWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KarnaughWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QComboBox *cbbSoBien;
    QComboBox *cbbDangBieuThuc;
    QCheckBox *chkDontCare;
    QPushButton *btnOK;
    QTableWidget *tableKetQua;
    QLineEdit *txtKetQua;
    QPushButton *btnBangTrangThai;
    QGroupBox *grpNhapTay;
    QLineEdit *txtMainTerms;
    QLineEdit *txtDontCares;
    QTableWidget *tableKMap;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *KarnaughWindow)
    {
        if (KarnaughWindow->objectName().isEmpty())
            KarnaughWindow->setObjectName("KarnaughWindow");
        KarnaughWindow->resize(800, 600);
        centralwidget = new QWidget(KarnaughWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(150, 30, 61, 21));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(130, 60, 111, 31));
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        cbbSoBien = new QComboBox(centralwidget);
        cbbSoBien->addItem(QString());
        cbbSoBien->addItem(QString());
        cbbSoBien->addItem(QString());
        cbbSoBien->addItem(QString());
        cbbSoBien->addItem(QString());
        cbbSoBien->addItem(QString());
        cbbSoBien->setObjectName("cbbSoBien");
        cbbSoBien->setGeometry(QRect(250, 30, 103, 32));
        cbbDangBieuThuc = new QComboBox(centralwidget);
        cbbDangBieuThuc->addItem(QString());
        cbbDangBieuThuc->addItem(QString());
        cbbDangBieuThuc->setObjectName("cbbDangBieuThuc");
        cbbDangBieuThuc->setGeometry(QRect(250, 60, 103, 32));
        chkDontCare = new QCheckBox(centralwidget);
        chkDontCare->setObjectName("chkDontCare");
        chkDontCare->setGeometry(QRect(430, 50, 161, 31));
        btnOK = new QPushButton(centralwidget);
        btnOK->setObjectName("btnOK");
        btnOK->setGeometry(QRect(160, 110, 141, 32));
        tableKetQua = new QTableWidget(centralwidget);
        tableKetQua->setObjectName("tableKetQua");
        tableKetQua->setGeometry(QRect(420, 180, 331, 271));
        txtKetQua = new QLineEdit(centralwidget);
        txtKetQua->setObjectName("txtKetQua");
        txtKetQua->setGeometry(QRect(140, 470, 551, 41));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        txtKetQua->setFont(font);
        txtKetQua->setAlignment(Qt::AlignmentFlag::AlignCenter);
        txtKetQua->setReadOnly(true);
        btnBangTrangThai = new QPushButton(centralwidget);
        btnBangTrangThai->setObjectName("btnBangTrangThai");
        btnBangTrangThai->setGeometry(QRect(420, 110, 161, 32));
        grpNhapTay = new QGroupBox(centralwidget);
        grpNhapTay->setObjectName("grpNhapTay");
        grpNhapTay->setEnabled(true);
        grpNhapTay->setGeometry(QRect(20, 200, 321, 151));
        txtMainTerms = new QLineEdit(grpNhapTay);
        txtMainTerms->setObjectName("txtMainTerms");
        txtMainTerms->setGeometry(QRect(10, 30, 301, 51));
        txtDontCares = new QLineEdit(grpNhapTay);
        txtDontCares->setObjectName("txtDontCares");
        txtDontCares->setGeometry(QRect(10, 100, 271, 31));
        QFont font1;
        font1.setBold(true);
        txtDontCares->setFont(font1);
        tableKMap = new QTableWidget(centralwidget);
        tableKMap->setObjectName("tableKMap");
        tableKMap->setGeometry(QRect(20, 180, 340, 272));
        KarnaughWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(KarnaughWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 36));
        KarnaughWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(KarnaughWindow);
        statusbar->setObjectName("statusbar");
        KarnaughWindow->setStatusBar(statusbar);

        retranslateUi(KarnaughWindow);

        QMetaObject::connectSlotsByName(KarnaughWindow);
    } // setupUi

    void retranslateUi(QMainWindow *KarnaughWindow)
    {
        KarnaughWindow->setWindowTitle(QCoreApplication::translate("KarnaughWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("KarnaughWindow", "S\341\273\221 bi\341\272\277n", nullptr));
        label_2->setText(QCoreApplication::translate("KarnaughWindow", "D\341\272\241ng bi\341\273\203u th\341\273\251c", nullptr));
        cbbSoBien->setItemText(0, QCoreApplication::translate("KarnaughWindow", "2", nullptr));
        cbbSoBien->setItemText(1, QCoreApplication::translate("KarnaughWindow", "3", nullptr));
        cbbSoBien->setItemText(2, QCoreApplication::translate("KarnaughWindow", "4", nullptr));
        cbbSoBien->setItemText(3, QCoreApplication::translate("KarnaughWindow", "5", nullptr));
        cbbSoBien->setItemText(4, QCoreApplication::translate("KarnaughWindow", "6", nullptr));
        cbbSoBien->setItemText(5, QCoreApplication::translate("KarnaughWindow", "7", nullptr));

        cbbDangBieuThuc->setItemText(0, QCoreApplication::translate("KarnaughWindow", "SOP", nullptr));
        cbbDangBieuThuc->setItemText(1, QCoreApplication::translate("KarnaughWindow", "POS", nullptr));

        chkDontCare->setText(QCoreApplication::translate("KarnaughWindow", "Ch\341\272\277 \304\221\341\273\231 Don't care (X)", nullptr));
        btnOK->setText(QCoreApplication::translate("KarnaughWindow", "B\341\272\243n \304\221\341\273\223 Karnaugh", nullptr));
        btnBangTrangThai->setText(QCoreApplication::translate("KarnaughWindow", "B\341\272\243ng tr\341\272\241ng th\303\241i", nullptr));
        grpNhapTay->setTitle(QCoreApplication::translate("KarnaughWindow", "Nh\341\272\255p gi\303\241 tr\341\273\213 th\341\273\247 c\303\264ng  (cho>4 bi\341\272\277n)", nullptr));
        txtDontCares->setPlaceholderText(QCoreApplication::translate("KarnaughWindow", "Nh\341\272\255p Don't Care", nullptr));
    } // retranslateUi

};

namespace Ui {
    class KarnaughWindow: public Ui_KarnaughWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KARNAUGHWINDOW_H
