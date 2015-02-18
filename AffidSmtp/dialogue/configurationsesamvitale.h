#ifndef CONFIGURATIONSESAMVITALE_H
#define CONFIGURATIONSESAMVITALE_H
#define CONFIG_SERVEUR  "CONFIG_SERV.ini"

#include <QDialog>
class QSettings;
class Configuration;

namespace Ui {
class ConfigurationSesamVitale;
}

class ConfigurationSesamVitale : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigurationSesamVitale(QWidget *parent = 0);
    ~ConfigurationSesamVitale();
    void showEvent(QShowEvent *event);

private:
    Ui::ConfigurationSesamVitale *ui;
    QSettings * fichierIni;
    Configuration * configServeur;

    void sauvegarderConfigurationServeur();

private slots:
    void validerCliquer();
    void parametreIdentiqueCliquer();
    void smtpSecuriserCliquer();
    void popSecuriserCliquer();
    void smtpAutentificationCliquer();
};

#endif // CONFIGURATIONSESAMVITALE_H
