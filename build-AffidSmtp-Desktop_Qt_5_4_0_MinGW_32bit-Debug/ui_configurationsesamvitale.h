/********************************************************************************
** Form generated from reading UI file 'configurationsesamvitale.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGURATIONSESAMVITALE_H
#define UI_CONFIGURATIONSESAMVITALE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_ConfigurationSesamVitale
{
public:
    QPushButton *valider;
    QPushButton *annuler;
    QPushButton *aide;
    QGroupBox *groupBox;
    QLabel *label;
    QGroupBox *groupBox_2;
    QGroupBox *groupBox_3;
    QRadioButton *radioButton;
    QGroupBox *groupBox_4;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QCheckBox *smtpAuth;
    QCheckBox *parametresConnexion;
    QLineEdit *identifiant;
    QLineEdit *password;
    QLineEdit *mail;
    QLineEdit *popServeur;
    QLineEdit *smtpServeur;
    QLineEdit *popPort;
    QLabel *label_12;
    QLineEdit *smtpPort;
    QLineEdit *identifiantconnexion;
    QLineEdit *passwordConnexion;
    QGroupBox *groupBox_5;
    QCheckBox *checkBox;

    void setupUi(QDialog *ConfigurationSesamVitale)
    {
        if (ConfigurationSesamVitale->objectName().isEmpty())
            ConfigurationSesamVitale->setObjectName(QStringLiteral("ConfigurationSesamVitale"));
        ConfigurationSesamVitale->resize(753, 667);
        ConfigurationSesamVitale->setStyleSheet(QLatin1String("QGroupBox\n"
"{\n"
"	border: 0.5px solid;\n"
"	border-radius:8px;\n"
"}"));
        valider = new QPushButton(ConfigurationSesamVitale);
        valider->setObjectName(QStringLiteral("valider"));
        valider->setGeometry(QRect(630, 30, 111, 31));
        annuler = new QPushButton(ConfigurationSesamVitale);
        annuler->setObjectName(QStringLiteral("annuler"));
        annuler->setGeometry(QRect(630, 70, 111, 31));
        aide = new QPushButton(ConfigurationSesamVitale);
        aide->setObjectName(QStringLiteral("aide"));
        aide->setGeometry(QRect(630, 110, 111, 31));
        groupBox = new QGroupBox(ConfigurationSesamVitale);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 601, 131));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 561, 101));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        groupBox_2 = new QGroupBox(ConfigurationSesamVitale);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 160, 591, 421));
        groupBox_2->setAlignment(Qt::AlignCenter);
        groupBox_3 = new QGroupBox(groupBox_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(70, 40, 151, 361));
        groupBox_3->setAlignment(Qt::AlignCenter);
        radioButton = new QRadioButton(groupBox_3);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(20, 140, 121, 41));
        radioButton->setChecked(true);
        groupBox_4 = new QGroupBox(groupBox_2);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(230, 40, 351, 361));
        groupBox_4->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(groupBox_4);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 20, 111, 21));
        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 50, 121, 21));
        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 80, 111, 21));
        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 110, 121, 21));
        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(30, 140, 181, 21));
        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(30, 170, 181, 21));
        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(30, 200, 181, 21));
        label_9 = new QLabel(groupBox_4);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(30, 230, 61, 21));
        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(30, 320, 61, 21));
        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(190, 320, 71, 21));
        smtpAuth = new QCheckBox(groupBox_4);
        smtpAuth->setObjectName(QStringLiteral("smtpAuth"));
        smtpAuth->setGeometry(QRect(70, 270, 251, 17));
        parametresConnexion = new QCheckBox(groupBox_4);
        parametresConnexion->setObjectName(QStringLiteral("parametresConnexion"));
        parametresConnexion->setGeometry(QRect(70, 290, 261, 17));
        identifiant = new QLineEdit(groupBox_4);
        identifiant->setObjectName(QStringLiteral("identifiant"));
        identifiant->setGeometry(QRect(150, 50, 191, 20));
        password = new QLineEdit(groupBox_4);
        password->setObjectName(QStringLiteral("password"));
        password->setGeometry(QRect(150, 80, 191, 20));
        mail = new QLineEdit(groupBox_4);
        mail->setObjectName(QStringLiteral("mail"));
        mail->setGeometry(QRect(150, 140, 191, 20));
        popServeur = new QLineEdit(groupBox_4);
        popServeur->setObjectName(QStringLiteral("popServeur"));
        popServeur->setGeometry(QRect(150, 170, 191, 20));
        smtpServeur = new QLineEdit(groupBox_4);
        smtpServeur->setObjectName(QStringLiteral("smtpServeur"));
        smtpServeur->setGeometry(QRect(150, 200, 191, 20));
        popPort = new QLineEdit(groupBox_4);
        popPort->setObjectName(QStringLiteral("popPort"));
        popPort->setGeometry(QRect(150, 230, 51, 20));
        label_12 = new QLabel(groupBox_4);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(230, 230, 61, 21));
        smtpPort = new QLineEdit(groupBox_4);
        smtpPort->setObjectName(QStringLiteral("smtpPort"));
        smtpPort->setGeometry(QRect(290, 230, 51, 20));
        identifiantconnexion = new QLineEdit(groupBox_4);
        identifiantconnexion->setObjectName(QStringLiteral("identifiantconnexion"));
        identifiantconnexion->setGeometry(QRect(90, 320, 81, 20));
        passwordConnexion = new QLineEdit(groupBox_4);
        passwordConnexion->setObjectName(QStringLiteral("passwordConnexion"));
        passwordConnexion->setGeometry(QRect(260, 320, 81, 20));
        groupBox_5 = new QGroupBox(ConfigurationSesamVitale);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(20, 590, 591, 61));
        groupBox_5->setAlignment(Qt::AlignCenter);
        checkBox = new QCheckBox(groupBox_5);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(350, 20, 221, 21));
        checkBox->setLayoutDirection(Qt::RightToLeft);

        retranslateUi(ConfigurationSesamVitale);

        QMetaObject::connectSlotsByName(ConfigurationSesamVitale);
    } // setupUi

    void retranslateUi(QDialog *ConfigurationSesamVitale)
    {
        ConfigurationSesamVitale->setWindowTitle(QApplication::translate("ConfigurationSesamVitale", "Dialog", 0));
        valider->setText(QApplication::translate("ConfigurationSesamVitale", "Valider", 0));
        annuler->setText(QApplication::translate("ConfigurationSesamVitale", "Annuler", 0));
        aide->setText(QApplication::translate("ConfigurationSesamVitale", "Aide", 0));
        groupBox->setTitle(QString());
        label->setText(QApplication::translate("ConfigurationSesamVitale", "Affid Vitale 4.1 - TLA - SESAM Vitale 1.40.5.2 \n"
" RSS XandMail API RSS 2.2 ESMTP AUTH Windows 95/NT 4 (c) Pine-3.91L (KIT CEGETEL 2.12)\n"
" WANADOO SANTE 3.02 ver1 - LIBERALIS 3, 3, 0 2001\n"
" INTERNET KIT AFFID 1.0", 0));
        groupBox_2->setTitle(QApplication::translate("ConfigurationSesamVitale", "Connexion au R\303\251seau SESAM - Vitale", 0));
        groupBox_3->setTitle(QApplication::translate("ConfigurationSesamVitale", "Fournisseur", 0));
        radioButton->setText(QApplication::translate("ConfigurationSesamVitale", "WANADOO SANTE", 0));
        groupBox_4->setTitle(QApplication::translate("ConfigurationSesamVitale", "Profil", 0));
        label_2->setText(QApplication::translate("ConfigurationSesamVitale", "Profil de connexion", 0));
        label_3->setText(QApplication::translate("ConfigurationSesamVitale", "Identifiant du compte", 0));
        label_4->setText(QApplication::translate("ConfigurationSesamVitale", "Mot de passe", 0));
        label_5->setText(QApplication::translate("ConfigurationSesamVitale", "Nom du fournisseur", 0));
        label_6->setText(QApplication::translate("ConfigurationSesamVitale", "Adresse de messagerie", 0));
        label_7->setText(QApplication::translate("ConfigurationSesamVitale", "Serveur Pop", 0));
        label_8->setText(QApplication::translate("ConfigurationSesamVitale", "Serveur SMTP", 0));
        label_9->setText(QApplication::translate("ConfigurationSesamVitale", "Port POP", 0));
        label_10->setText(QApplication::translate("ConfigurationSesamVitale", "Identifiant", 0));
        label_11->setText(QApplication::translate("ConfigurationSesamVitale", "Mot de passe", 0));
        smtpAuth->setText(QApplication::translate("ConfigurationSesamVitale", "Le serveur SMTP requiert une authentification", 0));
        parametresConnexion->setText(QApplication::translate("ConfigurationSesamVitale", "Utiliser des param\303\250tre de connexion identiques", 0));
        label_12->setText(QApplication::translate("ConfigurationSesamVitale", "Port SMTP", 0));
        groupBox_5->setTitle(QApplication::translate("ConfigurationSesamVitale", "Programmation de la t\303\251l\303\251transmission automatique", 0));
        checkBox->setText(QApplication::translate("ConfigurationSesamVitale", "Activer la trace de connexion", 0));
    } // retranslateUi

};

namespace Ui {
    class ConfigurationSesamVitale: public Ui_ConfigurationSesamVitale {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGURATIONSESAMVITALE_H
