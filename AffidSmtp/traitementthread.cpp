#include "traitementthread.h"
#include "./configuration.h"

#include <stdio.h>
#include <curllib/include/curl/curl.h>
#include <QtDebug>
#include <QTextStream>
#include <QDate>

// variables globales
int taille;
int valeur;
static QStringList toto;

CURL *curl;
CURLcode res = CURLE_OK;

static QString objet = "";
static QString body = "";
static QString to = "";
static QString from = "";

// callback de reception
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written;
    toto.append(QString::fromStdString((char *) ptr));
    written = fwrite(ptr, size, nmemb, stream);
    valeur = nmemb ;
    return written;
}

// méthodes pour l'envoi de mail
static char *payload_text[]  = {
  "Date: Mon, 29 Nov 2010 21:54:29 +1100\r\n",
  (char *) to.toStdString().c_str(),
  (char *) from.toStdString().c_str(),
  "Message-ID: <dcd7cb36-11db-487a-9f3a-e652a9458efd@rfcpedant.example.org>\r\n",
  (char *) objet.toStdString().c_str(),
  "\r\n", /* empty line to divide headers from body, see RFC5322*/
  (char *) body.toStdString().c_str(),
  "\r\n",
  "Check RFC5322.\r\n",
  NULL
};

struct upload_status {
  int lines_read;
};

static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
  struct upload_status *upload_ctx = (struct upload_status *)userp;
  const char *data;

  if((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
    return 0;
  }

  data = payload_text[upload_ctx->lines_read];

  if(data) {
    size_t len = strlen(data);
    memcpy(ptr, data, len);
    upload_ctx->lines_read++;

    return len;
  }

  return 0;
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
        reconstruireDataMail();
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

void TraitementThread::reconstruireDataMail()
{
      payload_text [0] = "Date: Mon, 29 Nov 2010 21:54:29 +1100\r\n";
      payload_text [1] = (char *) to.toStdString().c_str();
      payload_text [2] = (char *) from.toStdString().c_str();
      payload_text [3] = "Message-ID: < afid vitale >\r\n";
      payload_text [4] = (char *) objet.toStdString().c_str();
      payload_text [5] = "\r\n";
      payload_text [6] = (char *) body.toStdString().c_str();
      payload_text [7] = "\r\n";
      payload_text [8] = "Check RFC5322.\r\n";
      payload_text [9] = NULL ;

}

void TraitementThread::envoyerMail()
{

    qDebug() << (char *) payload_text;
    struct curl_slist *recipients = NULL;
    struct upload_status upload_ctx;

    upload_ctx.lines_read = 0;

    curl = curl_easy_init();
    if(curl) {
        emit sendTraitementEnCours(QString("Envoie du mail en cours"));
        curl_easy_setopt(curl, CURLOPT_USERNAME,
                        configServeur->getIdentifiantConnexion().toStdString().c_str());
        curl_easy_setopt(curl, CURLOPT_PASSWORD,
                        configServeur->getMostDePasseConnexion().toStdString().c_str());

        /* This is the URL for your mailserver. Note the use of smtps:// rather
        * than smtp:// to request a SSL based connection. */
        QString adresseSMTP ;
        if(configServeur->getSmtpSecuriser())
        {
           adresseSMTP = "smtps://";
           curl_easy_setopt(curl, CURLOPT_CAINFO, "./debug/certificat.pem");
           //curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
        }
        else
           adresseSMTP = "smtp://";

        adresseSMTP += configServeur->getAdressSMTP();
        if(configServeur->getRequiertAuthentification() && !configServeur->getSmtpSecuriser())
        {
            adresseSMTP += ":587";
            //curl_easy_setopt(curl, CURLOPT_CAINFO, "./debug/ca-bundle.crt");
        }
#ifdef SKIP_PEER_VERIFICATION
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
#endif
#ifdef SKIP_HOSTNAME_VERFICATION
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif
        curl_easy_setopt(curl, CURLOPT_URL, adresseSMTP.toStdString().c_str());

        curl_easy_setopt(curl, CURLOPT_MAIL_FROM,
                        configServeur->getAdresseMessagerie().toStdString().c_str());

        recipients = curl_slist_append(recipients, to.toStdString().c_str());
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        /* Send the message */
        res = curl_easy_perform(curl);

        /* Check for errors */
        if(res != CURLE_OK)
         fprintf(stderr, "curl_easy_perform() failed: %s\n",
                 curl_easy_strerror(res));

        /* Free the list of recipients */
        curl_slist_free_all(recipients);

        curl_easy_cleanup(curl);
    }
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
    objet   = "Subject: " + a_sujet + "\r\n" ;
    body    = a_body + "\r\n";
    to      =  a_to + "> \r\n";
    from    =  "FROM: <" + a_from + "> \r\n" ;
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
                curl_easy_setopt(curl, CURLOPT_CAINFO, "./debug/ca-bundle.crt");
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


