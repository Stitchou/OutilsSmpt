#include "curlinterprete.h"
#include "./dialogue/progression.h"
#include "../traitementthread.h"
#include "../dialogue/envoyermail.h"
#include "../configuration.h"

#include <QMessageBox>
#include <QDesktopServices>
#include <QDir>
#include <QUrl>

CurlInterprete::CurlInterprete(QObject *parent) : QObject(parent)
{
    // singleton de configuration serveur
    configServeur = Configuration::getInstance();

    progress = new Progression;
    threadCurl = new TraitementThread;
    envoyer = new EnvoyerMail;
    isOk = true;

    connect(threadCurl,SIGNAL(fini()),this,SLOT(terminerProgression()));
    connect(threadCurl,SIGNAL(sendTraitementEnCours(QString)),progress,SLOT(setMessage(QString)));
    connect(threadCurl,SIGNAL(erreur(QString)),this,SLOT(afficheErreur(QString)));
    connect(envoyer,SIGNAL(envoyerParams(QString,QString,QString,QString)),this,SLOT(recevoirParams(QString,QString,QString,QString)));
}

CurlInterprete::~CurlInterprete()
{

}

void CurlInterprete::listerMail()
{
    isOk = true;
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
        threadCurl->setParams(sujet,body,to,configServeur->getAdresseMessagerie(),pieceJointe);
        progress->show();
        threadCurl->start();
    }
}

void CurlInterprete::terminerProgression()
{
    progress->close();

    if( mode == TraitementThread::Lister &&  isOk)
    {
        QString path = "file:///"+QDir::currentPath()+"/liste_Mail.txt";
        QDesktopServices::openUrl(QUrl(path));
    }
}

void CurlInterprete::recevoirParams(QString a_to, QString a_subject, QString a_body,QString piece)
{
    to = a_to;
    body = a_body;
    sujet = a_subject;
    pieceJointe = piece;
}

void CurlInterprete::afficheErreur(QString msg)
{
    isOk = false;
    QMessageBox::warning(0,"Erreur de traitement",msg);
}


