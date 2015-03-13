#ifndef CURLINTERPRETE_H
#define CURLINTERPRETE_H

#include <QObject>

class Progression;
class TraitementThread;
class EnvoyerMail;
class Configuration;

class CurlInterprete : public QObject
{
    Q_OBJECT
public:
    explicit CurlInterprete(QObject *parent = 0);
    ~CurlInterprete();

    void listerMail();
    void envoyerNouveauMail();

private:
    Configuration * configServeur;
    Progression * progress;
    TraitementThread * threadCurl;
    EnvoyerMail *envoyer;
    int mode;

    QString sujet,body,to,pieceJointe;
    bool isOk;

signals:

private slots:
    void terminerProgression();
    void recevoirParams(QString a_to, QString a_subject, QString a_body, QString piece);
    void afficheErreur(QString msg);
};

#endif // CURLINTERPRETE_H
