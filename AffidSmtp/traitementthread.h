#ifndef TRAITEMENTTHREAD_H
#define TRAITEMENTTHREAD_H

#include <QObject>
#include <QThread>
#include <QFile>

class Configuration;

class TraitementThread : public QThread
{
    Q_OBJECT
    Q_ENUMS(Mode)
public:
    explicit TraitementThread(QObject *parent = 0);
    ~TraitementThread();
    void run();



    enum Mode
    {
        Lister,
        Envoyer
    };

    int getMode() const;
    void setMode(int value);
    void setParams(QString a_sujet, QString a_body, QString a_to, QString a_from);

signals:
    void sendTraitementEnCours(QString message);
    void fini();

public slots:

private:
    int mode;
    Configuration * configServeur;
    QFile *fic;
    QString contenue;

    void creerListeDeMail();
    void decouperListe();
    void listerMail();

    void reconstruireDataMail();
    void envoyerMail();
};

#endif // TRAITEMENTTHREAD_H
