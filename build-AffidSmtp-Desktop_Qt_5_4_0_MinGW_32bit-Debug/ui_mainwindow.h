/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *lister;
    QPushButton *envoyer;
    QPushButton *configurer;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(661, 337);
        MainWindow->setStyleSheet(QLatin1String("QGroupBox\n"
"{\n"
"	background: rgb(160,222,22);\n"
"	border:1px solid;\n"
"	border-radius:5px;\n"
"}\n"
"QWidget #centralWidget\n"
"{\n"
"	background: rgb(220,220,220);\n"
"}"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 641, 131));
        groupBox->setStyleSheet(QStringLiteral(""));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(150, 10, 331, 51));
        QFont font;
        font.setPointSize(36);
        label->setFont(font);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(230, 80, 161, 31));
        QFont font1;
        font1.setPointSize(20);
        label_2->setFont(font1);
        label_2->setAutoFillBackground(false);
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 170, 621, 131));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(25);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lister = new QPushButton(horizontalLayoutWidget);
        lister->setObjectName(QStringLiteral("lister"));
        lister->setMinimumSize(QSize(0, 50));
        QFont font2;
        font2.setPointSize(12);
        lister->setFont(font2);

        horizontalLayout->addWidget(lister);

        envoyer = new QPushButton(horizontalLayoutWidget);
        envoyer->setObjectName(QStringLiteral("envoyer"));
        envoyer->setMinimumSize(QSize(0, 50));
        envoyer->setFont(font2);

        horizontalLayout->addWidget(envoyer);

        configurer = new QPushButton(horizontalLayoutWidget);
        configurer->setObjectName(QStringLiteral("configurer"));
        configurer->setMinimumSize(QSize(0, 50));
        configurer->setFont(font2);

        horizontalLayout->addWidget(configurer);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        groupBox->setTitle(QString());
        label->setText(QApplication::translate("MainWindow", "Affid Syst\303\250mes", 0));
        label_2->setText(QApplication::translate("MainWindow", "Outils SMTP", 0));
        lister->setText(QApplication::translate("MainWindow", "Lister les mails", 0));
        envoyer->setText(QApplication::translate("MainWindow", "Envoyer un mail", 0));
        configurer->setText(QApplication::translate("MainWindow", "Configuration du service", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
