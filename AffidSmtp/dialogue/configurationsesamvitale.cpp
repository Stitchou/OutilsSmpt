#include "configurationsesamvitale.h"
#include "ui_configurationsesamvitale.h"

#include <QSettings>
#include "../configuration.h"

ConfigurationSesamVitale::ConfigurationSesamVitale(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationSesamVitale)
{
    ui->setupUi(this);
    this->setWindowTitle("Configuration du Réseau Sesam-Vitale");

    // construction fichier INI
    QString iniPath = CONFIG_SERVEUR;
    fichierIni = new QSettings(iniPath,QSettings::IniFormat);

    // singleton de configuration serveur
    configServeur = Configuration::getInstance();

    //connexions
    connect(ui->valider,SIGNAL(clicked()),this,SLOT(validerCliquer()));
    connect(ui->annuler,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->parametresConnexion,SIGNAL(clicked()),this,SLOT(parametreIdentiqueCliquer()));
    connect(ui->smtpSSL,SIGNAL(clicked()),this,SLOT(smtpSecuriserCliquer()));
    connect(ui->popAUTH,SIGNAL(clicked()),this,SLOT(popSecuriserCliquer()));
    connect(ui->smtpAuth,SIGNAL(clicked()),this,SLOT(smtpAutentificationCliquer()));

}

ConfigurationSesamVitale::~ConfigurationSesamVitale()
{
    delete fichierIni;
    delete configServeur;
    delete ui;
}

void ConfigurationSesamVitale::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    // lire configuration stocké
    configServeur->lireConfigurationServeur();

    ui->profil->setText(configServeur->getNomProfil());
    ui->identifiant->setText(configServeur->getIdentifiantCompte());
    ui->password->setText(configServeur->getMotDepasse());
    ui->fournisseur->setText(configServeur->getNomFAI());
    ui->mail->setText(configServeur->getAdresseMessagerie());
    ui->popServeur->setText(configServeur->getAdressePOP());
    ui->smtpServeur->setText(configServeur->getAdressSMTP());
    ui->popPort->setText(configServeur->getPortPOP());
    ui->smtpPort->setText(configServeur->getPortSMTP());   
    ui->identifiantconnexion->setText(configServeur->getIdentifiantConnexion());
    ui->passwordConnexion->setText(configServeur->getMostDePasseConnexion());

    ui->popAUTH->setChecked(configServeur->getPopSecuriser());
    ui->smtpAuth->setChecked(configServeur->getRequiertAuthentification());
    ui->smtpSSL->setChecked(configServeur->getSmtpSecuriser());
    ui->parametresConnexion->setChecked(configServeur->getParametresConnexionIdentique());

    smtpSecuriserCliquer();
    popSecuriserCliquer();
    parametreIdentiqueCliquer();

}

void ConfigurationSesamVitale::sauvegarderConfigurationServeur()
{
    fichierIni->setValue(tr("RESEAU/NOM_SERVEUR"),ui->profil->text());
    fichierIni->setValue(tr("RESEAU/IDENTIFIANT_COMPTE"),ui->identifiant->text());
    fichierIni->setValue(tr("RESEAU/MOT_DE_PASSE"),ui->password->text());
    fichierIni->setValue(tr("RESEAU/FOURNISSEUR"),ui->fournisseur->text());
    fichierIni->setValue(tr("RESEAU/MAIL"),ui->mail->text());
    fichierIni->setValue(tr("RESEAU/SERVEUR_POP"),ui->popServeur->text());
    fichierIni->setValue(tr("RESEAU/SERVEUR_SMTP"),ui->smtpServeur->text());
    fichierIni->setValue(tr("RESEAU/PORT_POP"),ui->popPort->text());
    fichierIni->setValue(tr("RESEAU/PORT_SMTP"),ui->smtpPort->text());
    fichierIni->setValue(tr("RESEAU/SMTP_AUTH"),ui->smtpAuth->isChecked());
    fichierIni->setValue(tr("RESEAU/PARAMETRE_CONNEXION"),ui->parametresConnexion->isChecked());
    fichierIni->setValue(tr("RESEAU/IDENTIFIANT_CONNEXION"),ui->identifiantconnexion->text());
    fichierIni->setValue(tr("RESEAU/MOT_DE_PASSE_CONNEXION"),ui->passwordConnexion->text());

    fichierIni->setValue(tr("RESEAU/POP_SECURE"),ui->popAUTH->isChecked());
    fichierIni->setValue(tr("RESEAU/SMTP_SECURE"),ui->smtpSSL->isChecked());


}

void ConfigurationSesamVitale::validerCliquer()
{
    sauvegarderConfigurationServeur();
    this->close();
}

void ConfigurationSesamVitale::parametreIdentiqueCliquer()
{
    if(ui->parametresConnexion->isChecked())
    {
        ui->identifiantconnexion->setEnabled(false);
        ui->identifiantconnexion->setText(ui->identifiant->text());
        ui->passwordConnexion->setEnabled(false);
        ui->passwordConnexion->setText(ui->password->text());
    }
    else
    {
        ui->identifiantconnexion->setEnabled(true);
        ui->identifiantconnexion->clear();;
        ui->passwordConnexion->setEnabled(true);
        ui->passwordConnexion->clear();
    }
}

void ConfigurationSesamVitale::smtpSecuriserCliquer()
{
    if(ui->smtpSSL->isChecked())
    {
        ui->smtpAuth->setChecked(true);
        ui->smtpPort->setText("465");
        ui->smtpAuth->setEnabled(false);
    }
    else
    {
        ui->smtpAuth->setEnabled(true);
        ui->smtpAuth->setChecked(false);
        ui->smtpPort->setText("25");
    }
}

void ConfigurationSesamVitale::popSecuriserCliquer()
{
    if(ui->popAUTH->isChecked())
    {
        ui->popPort->setText("995");
    }
    else
    {
        ui->popPort->setText("110");
    }
}

void ConfigurationSesamVitale::smtpAutentificationCliquer()
{
    if(ui->smtpAuth->isChecked())
    {
        ui->smtpPort->setText("587");
    }
    else
    {
        ui->smtpPort->setText("25");
    }
}
