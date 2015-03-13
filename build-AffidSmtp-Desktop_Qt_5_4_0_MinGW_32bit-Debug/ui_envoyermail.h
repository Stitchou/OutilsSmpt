/********************************************************************************
** Form generated from reading UI file 'envoyermail.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENVOYERMAIL_H
#define UI_ENVOYERMAIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_EnvoyerMail
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QGroupBox *groupBox_2;
    QTextEdit *body;
    QLineEdit *destinataire;
    QLineEdit *sujet;
    QLabel *label_3;
    QLineEdit *piece;
    QPushButton *valider;
    QPushButton *annuler;
    QPushButton *parcourir;

    void setupUi(QDialog *EnvoyerMail)
    {
        if (EnvoyerMail->objectName().isEmpty())
            EnvoyerMail->setObjectName(QStringLiteral("EnvoyerMail"));
        EnvoyerMail->resize(474, 397);
        groupBox = new QGroupBox(EnvoyerMail);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 10, 321, 371));
        groupBox->setStyleSheet(QLatin1String("QGroupBox\n"
"{\n"
"	border: 0.5px solid;\n"
"	border-radius:8px;\n"
"}"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 81, 21));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 50, 81, 21));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 120, 281, 231));
        body = new QTextEdit(groupBox_2);
        body->setObjectName(QStringLiteral("body"));
        body->setGeometry(QRect(10, 20, 261, 231));
        destinataire = new QLineEdit(groupBox);
        destinataire->setObjectName(QStringLiteral("destinataire"));
        destinataire->setGeometry(QRect(90, 20, 201, 20));
        sujet = new QLineEdit(groupBox);
        sujet->setObjectName(QStringLiteral("sujet"));
        sujet->setGeometry(QRect(90, 50, 201, 20));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 83, 71, 16));
        piece = new QLineEdit(groupBox);
        piece->setObjectName(QStringLiteral("piece"));
        piece->setGeometry(QRect(90, 80, 201, 20));
        valider = new QPushButton(EnvoyerMail);
        valider->setObjectName(QStringLiteral("valider"));
        valider->setGeometry(QRect(350, 20, 111, 31));
        annuler = new QPushButton(EnvoyerMail);
        annuler->setObjectName(QStringLiteral("annuler"));
        annuler->setGeometry(QRect(350, 60, 111, 31));
        parcourir = new QPushButton(EnvoyerMail);
        parcourir->setObjectName(QStringLiteral("parcourir"));
        parcourir->setGeometry(QRect(350, 100, 111, 31));
        parcourir->setMinimumSize(QSize(80, 25));
        parcourir->setMaximumSize(QSize(6333, 63666));
        QWidget::setTabOrder(destinataire, sujet);
        QWidget::setTabOrder(sujet, body);
        QWidget::setTabOrder(body, valider);
        QWidget::setTabOrder(valider, annuler);

        retranslateUi(EnvoyerMail);

        QMetaObject::connectSlotsByName(EnvoyerMail);
    } // setupUi

    void retranslateUi(QDialog *EnvoyerMail)
    {
        EnvoyerMail->setWindowTitle(QApplication::translate("EnvoyerMail", "Dialog", 0));
        groupBox->setTitle(QString());
        label->setText(QApplication::translate("EnvoyerMail", "Destinataire", 0));
        label_2->setText(QApplication::translate("EnvoyerMail", "Sujet", 0));
        groupBox_2->setTitle(QApplication::translate("EnvoyerMail", "Message", 0));
        label_3->setText(QApplication::translate("EnvoyerMail", "Pi\303\250ce jointe", 0));
        valider->setText(QApplication::translate("EnvoyerMail", "Valider", 0));
        annuler->setText(QApplication::translate("EnvoyerMail", "Annuler", 0));
        parcourir->setText(QApplication::translate("EnvoyerMail", "Parcourir", 0));
    } // retranslateUi

};

namespace Ui {
    class EnvoyerMail: public Ui_EnvoyerMail {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENVOYERMAIL_H
