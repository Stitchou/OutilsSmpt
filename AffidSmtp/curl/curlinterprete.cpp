#include "curlinterprete.h"
#include "./dialogue/progression.h"
#include "../traitementthread.h"
#include "../dialogue/envoyermail.h"
#include "../configuration.h"

#include <QMessageBox>
#include <QDesktopServices>
#include <QApplication>
#include <QUrl>

CurlInterprete::CurlInterprete(QObject *parent) : QObject(parent)
{
    // singleton de configuration serveur
    configServeur = Configuration::getInstance();

    progress = new Progression;
    threadCurl = new TraitementThread;
    envoyer = new EnvoyerMail;

    connect(threadCurl,SIGNAL(fini()),this,SLOT(terminerProgression()));
    connect(threadCurl,SIGNAL(sendTraitementEnCours(QString)),progress,SLOT(setMessage(QString)));
    connect(envoyer,SIGNAL(envoyerParams(QString,QString,QString)),this,SLOT(recevoirParams(QString,QString,QString)));
}

CurlInterprete::~CurlInterprete()
{

}

void CurlInterprete::listerMail()
{
    mode = TraitementThread::Lister;
    threadCurl->setMode(mode);
    progress->show();
    threadCurl->start();
}

void CurlInterprete::envoyerNouveauMail()
{
    int retour = envoyer->exec();
    if( retour == 0)
    {
        mode = TraitementThread::Envoyer;
        threadCurl->setMode(TraitementThread::Envoyer);
        configServeur->lireConfigurationServeur();
        threadCurl->setParams(sujet,body,to,configServeur->getAdresseMessagerie());
        progress->show();
        threadCurl->start();
    }
}

void CurlInterprete::terminerProgression()
{
    progress->close();

    if( mode == TraitementThread::Lister)
    {
        QString path = "file:///"+QApplication::applicationDirPath()+"/liste_Mail.txt";
        QDesktopServices::openUrl(QUrl(path));
    }
}

void CurlInterprete::recevoirParams(QString a_to, QString a_subject, QString a_body)
{
    to = a_to;
    body = a_body;
    sujet = a_subject;
}


