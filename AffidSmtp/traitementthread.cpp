#include "traitementthread.h"
#include "./configuration.h"

#include <stdio.h>
#include <curllib/include/curl/curl.h>
#include <QtDebug>
#include <QTextStream>
#include <QDate>
#include <QDir>
#include <QProcess>

// variables globales
int taille;
int valeur;
static QStringList toto;

CURL *curl;
CURLcode res = CURLE_OK;

// callback de reception
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written;
    toto.append(QString::fromStdString((char *) ptr));
    written = fwrite(ptr, size, nmemb, stream);
    valeur = nmemb ;
    return written;
}

TraitementThread::TraitementThread(QObject *parent) : QThread(parent)
{
    // singleton de configuration serveur
    configServeur = Configuration::getInstance();
    fic = new QFile("./debug/liste_Mail.txt");
}

TraitementThread::~TraitementThread()
{
    delete fic;
}

void TraitementThread::run()
{
    configServeur->lireConfigurationServeur();
    if(mode == TraitementThread::Lister)
    {
        listerMail();
    }
    else if(mode == TraitementThread::Envoyer)
    {
        envoyerMail2();
    }
}

void TraitementThread::listerMail()
{
    emit sendTraitementEnCours(QString("Enumération des mails"));
    // effacement du fichier de sauvegarde
    contenue.clear();

    curl = curl_easy_init();
    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_USERNAME,
                         configServeur->getIdentifiantConnexion().toStdString().c_str());
        curl_easy_setopt(curl, CURLOPT_PASSWORD,
                         configServeur->getMostDePasseConnexion().toStdString().c_str());

        // Création de l'adresse pop
        QString adressePop ;
        if(configServeur->getPopSecuriser())
        {
            adressePop = "pop3s://";
            curl_easy_setopt(curl, CURLOPT_CAINFO, "./debug/ca-bundle.crt");
        }
        else
            adressePop = "pop3://";

        adressePop += configServeur->getAdressePOP();        
        curl_easy_setopt(curl, CURLOPT_URL,adressePop.toStdString().c_str());

        // callback de sauvegarde
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
        {
          QString stderre = QString( "curl_easy_perform() failed: %1\n").arg(
                      curl_easy_strerror(res));
            qDebug() << stderre;
        }
        curl_easy_cleanup(curl);
    }

    emit sendTraitementEnCours(QString("Fin de la recherche"));
    this->sleep(1);
    creerListeDeMail();
}


void TraitementThread::envoyerMail2()
{
    /*curl --url "smtp://smtp.live.com:587"
     * --ssl-reqd
     * --mail-from "e.imbart@hotmail.fr"
     * --mail-rcpt "lovermaki@hotmail.fr"
     * --upload-file mail.txt
     * --user "e.imbart@hotmail.fr:Clarisse"
     * --insecure
    ping 127.0.0.1 -n 2 > toto.txt
    exit*/
    contenue.clear();

    contenue =  "From: <"+mailFrom+"> \r\n";
    contenue += "To: <" + mailTo + "> \r\n";
    contenue += "Subject: " + mailObject + "\r\n";
    contenue += "\r\n";
    contenue += mailBody;

    fic->setFileName("mail.txt");
    fic->open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream flux(fic);
    flux.setCodec("UTF-8");
    flux << contenue;
    fic->close();

    QProcess * cmd = new QProcess;
    QStringList arg;
    emit sendTraitementEnCours(QString("Envoie du mail en cours"));


    QString adresseSMTP ;
    if(configServeur->getSmtpSecuriser())
    {
       adresseSMTP = "smtps://";
    }
    else
       adresseSMTP = "smtp://";
    adresseSMTP += configServeur->getAdressSMTP();
    if(configServeur->getRequiertAuthentification() && !configServeur->getSmtpSecuriser())
    {
        adresseSMTP += ":587";
    }

    // construction des arguments
    arg << "--url" << adresseSMTP;

    if(     (configServeur->getRequiertAuthentification() && !configServeur->getSmtpSecuriser())
       ||   (configServeur->getSmtpSecuriser())
      )
        arg << "--ssl-reqd";

    arg << "--mail-from" << mailFrom
        << "--mail-rcpt" << mailTo
        << "--upload-file" << "mail.txt"
        << "--user" << configServeur->getIdentifiantConnexion()+":"+configServeur->getMostDePasseConnexion();

    if(configServeur->getLogActions())
        arg << "> toto.txt";
    qDebug () << arg;

    cmd->execute("curl.exe",arg);


    //fic->remove();
    this->sleep(1);
    emit fini();
}
int TraitementThread::getMode() const
{
    return mode;
}

void TraitementThread::setMode(int value)
{
    mode = value;
}

void TraitementThread::setParams(QString a_sujet, QString a_body, QString a_to, QString a_from)
{
    mailBody = a_body;
    mailFrom = a_from;
    mailTo = a_to;
    mailObject = a_sujet;
}

void TraitementThread::creerListeDeMail()
{
    QStringList compteur = toto;
    toto.clear();


    for(int i = 0; i < compteur.size(); i+=2)
    {
        emit sendTraitementEnCours(QString("Début du listing"));

        curl = curl_easy_init();
        if(curl)
        {
            curl_easy_setopt(curl, CURLOPT_USERNAME,
                             configServeur->getIdentifiantConnexion().toStdString().c_str());
            curl_easy_setopt(curl, CURLOPT_PASSWORD,
                             configServeur->getMostDePasseConnexion().toStdString().c_str());

            // Création de l'adresse pop
            QString adressePop ;
            if(configServeur->getPopSecuriser())
            {
                adressePop = "pop3s://";
                curl_easy_setopt(curl, CURLOPT_CAINFO, "./debug/curl-ca-bundle.crt");
            }
            else
                adressePop = "pop3://";

            adressePop += configServeur->getAdressePOP() + "/"+compteur.at(i).left(compteur.at(i).indexOf(" "));
            curl_easy_setopt(curl, CURLOPT_URL,adressePop.toStdString().c_str());

            // callback de sauvegarde
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

            res = curl_easy_perform(curl);

            if(res != CURLE_OK)
            {
              QString stderre = QString( "curl_easy_perform() failed: %1\n").arg(
                          curl_easy_strerror(res));
                qDebug() << stderre;
            }
            curl_easy_cleanup(curl);
        }
        decouperListe();
    }
    emit sendTraitementEnCours(QString("Fin du listing"));

    fic->open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream flux(fic);
    flux.setCodec("UTF-8");
    flux << contenue;
    fic->close();

    this->sleep(1);
    emit fini();
}

void TraitementThread::decouperListe()
{
    QStringList lignes;
    QString from,to,subject;
    int thatAll = 0;
    bool isValide = false;
    for(int i = 0; i < toto.size(); i++)
    {
        lignes = toto.at(i).split("\r\n");
       for(int j =0; j < lignes.size(); j++)
       {
           if(lignes.at(j).contains("Message-Id"))
               isValide = true;

            if(lignes.at(j).contains("From:") && isValide && from.isEmpty())
            {
                thatAll++;
                from = lignes.at(j) + " - ";
            }
            if(lignes.at(j).contains("Subject:") && isValide && subject.isEmpty())
            {
                thatAll++;
                subject = lignes.at(j) + " - ";
            }
            if(lignes.at(j).contains("To:") && !lignes.at(j).contains("In-Reply-To")
               && isValide && to.isEmpty())
            {
                thatAll++;
                to = lignes.at(j) + " \r\n" ;
            }
            if(thatAll == 3)
            {
                isValide = false;
                break;
            }
       }
       if(thatAll == 3)
           break;
    }
    contenue += from + subject + to ;
    toto.clear();
}


