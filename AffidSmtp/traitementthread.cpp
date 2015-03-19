#include "traitementthread.h"
#include "./configuration.h"

#include <stdio.h>
#include <curllib/include/curl/curl.h>
#include <string.h>
#include <QtDebug>
#include <QTextStream>
#include <QDate>
#include <QDir>
#include <QProcess>
#include <math.h>
#include <smtpQt/SmtpMime>

#define MULTI_PERFORM_HANG_TIMEOUT 60 * 1000

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

static size_t read_callback(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
  size_t retcode = fread(ptr, size, nmemb, stream);

  return retcode;
}

TraitementThread::TraitementThread(QObject *parent) : QThread(parent)
{
    // singleton de configuration serveur
    configServeur = Configuration::getInstance();
    fic = new QFile("liste_Mail.txt");
    cmd = new QProcess;
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
        envoyerMail();
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
            curl_easy_setopt(curl, CURLOPT_CAINFO, "./curl-ca-bundle.crt");
        }
        else
            adressePop = "pop3://";

        adressePop += configServeur->getAdressePOP();        
        curl_easy_setopt(curl, CURLOPT_URL,adressePop.toStdString().c_str());

        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
        {
            QString err = QString("curl_easy_perform() failed: %1\n").arg(curl_easy_strerror(res));
            emit erreur(err);
        }
        curl_easy_cleanup(curl);
    }

    emit sendTraitementEnCours(QString("Fin de la recherche"));
    this->sleep(1);
    creerListeDeMail();
}

void TraitementThread::reformater()
{
    QFile fic("mail.txt");

    if(fic.open(QIODevice::WriteOnly))
    {
        QTextStream flux(&fic);

        QString formatage = "Date: "+QDate::currentDate().toString("ddd, dd MMM yyyy") +" "+
                            QTime::currentTime().toString("hh:mm:ss")+" GMT\r\n";

        flux << formatage;

        MimeMessage message;
        message.setSender(new EmailAddress(mailFrom, mailFrom.left(mailFrom.indexOf("@"))));
        message.addRecipient(new EmailAddress(mailTo, mailTo.left(mailTo.indexOf("@"))));
        message.setSubject(mailObject);

        // Add some text

        MimeText text;
        text.setText(mailBody);
        message.addPart(&text);

        // Add an another attachment
        message.addPart(new MimeAttachment(new QFile(pieceJointe)));

        flux << message.toString();
        fic.close();
    }
}

void TraitementThread::envoyerMail()
{
    emit sendTraitementEnCours(QString("Chargement de la pièce jointe"));
    FILE *file_debug=NULL;
    QString path = QDir::currentPath()+"/toto.txt";
    file_debug = fopen(path.toStdString().c_str(), "a+");   //open the specified file on local host

    reformater();

    FILE *hd_src;
    path = QDir::currentPath()+"/mail.txt";
    hd_src = fopen(path.toStdString().c_str(), "r");

    struct curl_slist *recipients = NULL;

    curl = curl_easy_init();
   // file_size = read_file();

    if(curl)
    {
        emit sendTraitementEnCours(QString("Envoie du mail en cours"));
        // usernamse
        curl_easy_setopt(curl, CURLOPT_USERNAME,
                        configServeur->getIdentifiantConnexion().toStdString().c_str());
        // password
        curl_easy_setopt(curl, CURLOPT_PASSWORD,
                        configServeur->getMostDePasseConnexion().toStdString().c_str());

        QString adresseSMTP ;
        if(configServeur->getSmtpSecuriser())
        {
           adresseSMTP = "smtps://";
           curl_easy_setopt(curl, CURLOPT_CAINFO, "./certificat.pem");
           curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        }
        else
           adresseSMTP = "smtp://";

        adresseSMTP += configServeur->getAdressSMTP();
        if(configServeur->getRequiertAuthentification() && !configServeur->getSmtpSecuriser())
        {
            adresseSMTP += ":587";
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        }
        // adresse smtp
        curl_easy_setopt(curl, CURLOPT_URL, adresseSMTP.toStdString().c_str());
        // From
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM,
                                configServeur->getAdresseMessagerie().toStdString().c_str());
        //TO
        recipients = curl_slist_append(recipients, mailTo.toStdString().c_str());
                curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
        curl_easy_setopt(curl, CURLOPT_READDATA, hd_src);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        if(configServeur->getLogActions())
        {
            curl_easy_setopt(curl, CURLOPT_STDERR,file_debug);
        }

        /* Send the message */

        res = curl_easy_perform(curl);

      // fermeture des fichiers
      fclose(file_debug);
      fclose(hd_src);

      // log
      if(configServeur->getLogActions())
          ecrirelog(1);

      this->sleep(1);
      emit fini();
   }

}

void TraitementThread::ecrirelog(int mode)
{
    QFile lire,ajout("logs_connexion.txt");
    if( mode == 0)
        lire.setFileName("logs.txt");
    else
        lire.setFileName("toto.txt");
    if(lire.open(QIODevice::ReadOnly))
    {
        if(ajout.open(QIODevice::Append))
        {
            QTextStream flux(&lire);
            QTextStream flux2(&ajout);
            flux2 <<"\r\n\r\n\r\n"+ QDate::currentDate().toString("dddd dd MMMM yyyy") + "   "+ QTime::currentTime().toString("hh:mm:ss") + "\r\n\r\n";
            if(mode == 0)
                flux2 << " LISTING\r\n";
            else
                flux2 << " ENVOI\r\n";
            flux2 << " ----------------------\r\n\r\n ";
            flux2 << flux.readAll();
            flux2 << "\r\n\r\n ---------------------- ";
            flux2 << "\r\n fin \r\n";
            lire.close();
            lire.remove();
            ajout.close();
        }
    }
}

void TraitementThread::readOutput()
{
    cmd->close();
}
int TraitementThread::getMode() const
{
    return mode;
}

void TraitementThread::setMode(int value)
{
    mode = value;
}

void TraitementThread::setParams(QString a_sujet, QString a_body, QString a_to, QString a_from, QString piece)
{
    mailBody = a_body;
    mailFrom = a_from;
    mailTo = a_to;
    mailObject = a_sujet;
    pieceJointe = piece;
}

void TraitementThread::creerListeDeMail()
{
    QStringList compteur = toto;
    toto.clear();
    FILE *file_debug=NULL;
    QString path = QDir::currentPath()+"/logs.txt";
    file_debug = fopen(path.toStdString().c_str(), "a+");

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
                curl_easy_setopt(curl, CURLOPT_CAINFO, "./curl-ca-bundle.crt");
            }
            else
                adressePop = "pop3://";

            adressePop += configServeur->getAdressePOP() + "/"+compteur.at(i).left(compteur.at(i).indexOf(" "));
            curl_easy_setopt(curl, CURLOPT_URL,adressePop.toStdString().c_str());

            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            if(configServeur->getLogActions())
            {
                curl_easy_setopt(curl, CURLOPT_STDERR,file_debug);
            }
            res = curl_easy_perform(curl);

            if(res != CURLE_OK)
            {
                QString err = QString("curl_easy_perform() failed: %1\n").arg(curl_easy_strerror(res));
                emit erreur(err);
            }

            curl_easy_cleanup(curl);
        }
        decouperListe();
    }
    fclose(file_debug);
    emit sendTraitementEnCours(QString("Fin du listing"));

    fic->open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream flux(fic);
    flux.setCodec("UTF-8");
    flux << contenue;
    fic->close();
    if(configServeur->getLogActions())
        ecrirelog(0);
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
    if(subject.contains(configServeur->getAdelie()))
        contenue += from + subject + to ;
    toto.clear();
}


