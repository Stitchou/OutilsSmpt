#include "configuration.h"

#include <QSettings>

Configuration *Configuration::configurationInstance = NULL;

Configuration *Configuration::getInstance()
{
    if (!configurationInstance)   // Only allow one instance of class to be generated.
    {
        configurationInstance = new Configuration;
    }
    return configurationInstance;
}

Configuration::Configuration()
{
    // construction fichier INI
    QString iniPath = CONFIG_SERVEUR;
    fichierIni = new QSettings(iniPath,QSettings::IniFormat);

    nomProfil               = "";
    identifiantCompte       = "";
    motDepasse              = "";
    nomFAI                  = "";
    adresseMessagerie       = "";
    adressePOP              = "";
    adressSMTP              = "";
    identifiantConnexion    = "";
    mostDePasseConnexion    = "";
    portPOP                 = "";
    portSMTP                = "";
    adelie = "";

    requiertAuthentification     = true;
    parametresConnexionIdentique = true;


}
QString Configuration::getAdelie() const
{
    return adelie;
}

void Configuration::setAdelie(const QString &value)
{
    adelie = value;
}

bool Configuration::getLogActions() const
{
    return logActions;
}

void Configuration::setLogActions(bool value)
{
    logActions = value;
}

bool Configuration::getSmtpSecuriser() const
{
    return smtpSecuriser;
}

void Configuration::setSmtpSecuriser(bool value)
{
    smtpSecuriser = value;
}

bool Configuration::getPopSecuriser() const
{
    return popSecuriser;
}

void Configuration::setPopSecuriser(bool value)
{
    popSecuriser = value;
}

QString Configuration::getIdentifiantConnexion() const
{
    return identifiantConnexion;
}

void Configuration::setIdentifiantConnexion(const QString &value)
{
    identifiantConnexion = value;
}
QString Configuration::getMostDePasseConnexion() const
{
    return mostDePasseConnexion;
}

void Configuration::setMostDePasseConnexion(const QString &value)
{
    mostDePasseConnexion = value;
}
bool Configuration::getRequiertAuthentification() const
{
    return requiertAuthentification;
}

void Configuration::setRequiertAuthentification(bool value)
{
    requiertAuthentification = value;
}
bool Configuration::getParametresConnexionIdentique() const
{
    return parametresConnexionIdentique;
}

void Configuration::setParametresConnexionIdentique(bool value)
{
    parametresConnexionIdentique = value;
}

void Configuration::lireConfigurationServeur()
{
    configurationInstance->setNomProfil(fichierIni->value(tr("RESEAU/NOM_SERVEUR"),"").toString());
    configurationInstance->setIdentifiantCompte(fichierIni->value(tr("RESEAU/IDENTIFIANT_COMPTE"),"").toString());
    configurationInstance->setMotDepasse(fichierIni->value(tr("RESEAU/MOT_DE_PASSE"),"").toString());
    configurationInstance->setNomFAI(fichierIni->value(tr("RESEAU/FOURNISSEUR"),"").toString());
    configurationInstance->setAdresseMessagerie(fichierIni->value(tr("RESEAU/MAIL"),"").toString());
    configurationInstance->setAdressePOP(fichierIni->value(tr("RESEAU/SERVEUR_POP"),"").toString());
    configurationInstance->setAdressSMTP(fichierIni->value(tr("RESEAU/SERVEUR_SMTP"),"").toString());
    configurationInstance->setPortPOP(fichierIni->value(tr("RESEAU/PORT_POP"),"").toString());
    configurationInstance->setPortSMTP(fichierIni->value(tr("RESEAU/PORT_SMTP"),"").toString());
    configurationInstance->setRequiertAuthentification(fichierIni->value(tr("RESEAU/SMTP_AUTH"),"true").toBool());
    configurationInstance->setPopSecuriser(fichierIni->value(tr("RESEAU/POP_SECURE"),"false").toBool());
    configurationInstance->setSmtpSecuriser(fichierIni->value(tr("RESEAU/SMTP_SECURE"),"false").toBool());
    configurationInstance->setParametresConnexionIdentique(fichierIni->value(tr("RESEAU/PARAMETRE_CONNEXION"),"true").toBool());
    configurationInstance->setIdentifiantConnexion(fichierIni->value(tr("RESEAU/IDENTIFIANT_CONNEXION"),"").toString());
    configurationInstance->setMostDePasseConnexion(fichierIni->value(tr("RESEAU/MOT_DE_PASSE_CONNEXION"),"").toString());
    configurationInstance->setLogActions(fichierIni->value(tr("RESEAU/LOG"),"false").toBool());
    configurationInstance->setAdelie(fichierIni->value(tr("RESEAU/NUM_ADELIE"),"").toString());
}

QString Configuration::getPortSMTP() const
{
    return portSMTP;
}

void Configuration::setPortSMTP(QString value)
{
    portSMTP = value;
}

QString Configuration::getPortPOP() const
{
    return portPOP;
}

void Configuration::setPortPOP(QString value)
{
    portPOP = value;
}

QString Configuration::getAdressSMTP() const
{
    return adressSMTP;
}

void Configuration::setAdressSMTP(const QString &value)
{
    adressSMTP = value;
}

QString Configuration::getAdressePOP() const
{
    return adressePOP;
}

void Configuration::setAdressePOP(const QString &value)
{
    adressePOP = value;
}

QString Configuration::getAdresseMessagerie() const
{
    return adresseMessagerie;
}

void Configuration::setAdresseMessagerie(const QString &value)
{
    adresseMessagerie = value;
}

QString Configuration::getNomFAI() const
{
    return nomFAI;
}

void Configuration::setNomFAI(const QString &value)
{
    nomFAI = value;
}

QString Configuration::getMotDepasse() const
{
    return motDepasse;
}

void Configuration::setMotDepasse(const QString &value)
{
    motDepasse = value;
}

QString Configuration::getIdentifiantCompte() const
{
    return identifiantCompte;
}

void Configuration::setIdentifiantCompte(const QString &value)
{
    identifiantCompte = value;
}

QString Configuration::getNomProfil() const
{
    return nomProfil;
}

void Configuration::setNomProfil(const QString &value)
{
    nomProfil = value;
}


