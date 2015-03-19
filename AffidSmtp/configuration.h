#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#define CONFIG_SERVEUR  "CONFIG_SERV.ini"

#include <QObject>
class QSettings;

class Configuration : public QObject
{
    Q_OBJECT
public:
    static Configuration * getInstance();

    QString getNomProfil() const;
    void setNomProfil(const QString &value);

    QString getIdentifiantCompte() const;
    void setIdentifiantCompte(const QString &value);

    QString getMotDepasse() const;
    void setMotDepasse(const QString &value);

    QString getNomFAI() const;
    void setNomFAI(const QString &value);

    QString getAdresseMessagerie() const;
    void setAdresseMessagerie(const QString &value);

    QString getAdressePOP() const;
    void setAdressePOP(const QString &value);

    QString getAdressSMTP() const;
    void setAdressSMTP(const QString &value);

    QString getPortPOP() const;
    void setPortPOP(QString value);

    QString getPortSMTP() const;
    void setPortSMTP(QString value);

    QString getIdentifiantConnexion() const;
    void setIdentifiantConnexion(const QString &value);

    QString getMostDePasseConnexion() const;
    void setMostDePasseConnexion(const QString &value);

    bool getRequiertAuthentification() const;
    void setRequiertAuthentification(bool value);

    bool getParametresConnexionIdentique() const;
    void setParametresConnexionIdentique(bool value);

    void lireConfigurationServeur();

    bool getPopSecuriser() const;
    void setPopSecuriser(bool value);

    bool getSmtpSecuriser() const;
    void setSmtpSecuriser(bool value);

    bool getLogActions() const;
    void setLogActions(bool value);

    QString getAdelie() const;
    void setAdelie(const QString &value);

private:
    static Configuration * configurationInstance;
    Configuration();

    QString nomProfil;
    QString identifiantCompte;
    QString motDepasse;
    QString nomFAI;
    QString adresseMessagerie;
    QString adressePOP;
    QString adressSMTP;
    QString identifiantConnexion;
    QString mostDePasseConnexion;
    QString portPOP;
    QString portSMTP;
    QString adelie;

    bool    requiertAuthentification;
    bool    parametresConnexionIdentique;
    bool    popSecuriser;
    bool    smtpSecuriser;
    bool    logActions;

    QSettings * fichierIni;
signals:

public slots:
};

#endif // CONFIGURATION_H
