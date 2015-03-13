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
#define MULTI_PERFORM_HANG_TIMEOUT 60 * 1000

// variables globales
int taille;
int valeur;
static QStringList toto;

static const int CHARS= 76;			//Sending 54 chararcters at a time with \r , \n and \0 it becomes 57
static const int ADD_SIZE= 20;			// ADD_SIZE for TO,FROM,SUBJECT,CONTENT-TYPE,CONTENT-TRANSFER-ENCODING,CONETNT-DISPOSITION and \r\n
static const int SEND_BUF_SIZE= 54;
static char (*fileBuf)[CHARS] = NULL;

QString PJ;
QString mailFrom, mailTo, mailBody, mailObject,pieceJointe;

CURL *curl;
CURLcode res = CURLE_OK;
CURLM *mcurl;

// callback de reception
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written;
    toto.append(QString::fromStdString((char *) ptr));
    written = fwrite(ptr, size, nmemb, stream);
    valeur = nmemb ;
    return written;
}

struct fileBuf_upload_status
{
  int lines_read;
};

static size_t read_callback(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
  size_t retcode = fread(ptr, size, nmemb, stream);

  return retcode;
}

static const char b64_table[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static void encodeblock( char *in, char *out, int len )
{
    out[0] = (unsigned char) b64_table[ (int)(in[0] >> 2) ];
    out[1] = (unsigned char) b64_table[ (int)(((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4)) ];
    out[2] = (unsigned char) (len > 1 ? b64_table[ (int)(((in[1] & 0x0f) << 2) | ((in[2] & 0xc0) >> 6)) ] : '=');
    out[3] = (unsigned char) (len > 2 ? b64_table[ (int)(in[2] & 0x3f) ] : '=');
}

void base64_encode(char *input_buf, char *output_buf)
{
    char in[3], out[4];
    size_t len = strlen(input_buf);

    *output_buf = 0;
    for (size_t i=0; i<len; )
    {
        int buf3_len = 0;
        for (int j=0; j<3; ++j)
        {
            in[j] = input_buf[i++];
            if (i > len)
                in[j] = 0;
            else
                buf3_len++;
        }
        if (len>0)
        {
            encodeblock(in,out,buf3_len);
            strncat(output_buf, out, 4);
        }
    }
}

static size_t fileBuf_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
    struct fileBuf_upload_status *upload_ctx = (struct fileBuf_upload_status *)userp;
    const char *fdata;

    if((size == 0) || (nmemb == 0) || ((size*nmemb) < 1))
    {
        return 0;
    }

    fdata = fileBuf[upload_ctx->lines_read];

    if(strcmp(fdata,""))
    {
        size_t len = strlen(fdata);
        memcpy(ptr, fdata, len);
        upload_ctx->lines_read++;
        return len;
    }
    return 0;
}
size_t read_file()
{
    FILE* hFile=NULL;
    size_t fileSize(0),len(0),buffer_size(0);

    //opening the file
    hFile = fopen(PJ.toStdString().c_str(),"rb");
    if (hFile == NULL)
        throw "File Does not exist.";

    //get file size
    fseek(hFile,0,SEEK_END);
    fileSize = ftell(hFile);
    fseek(hFile,0,SEEK_SET);

    //Checking file size
    if(fileSize > 1*1024)
    {}

    QString filename = pieceJointe;
    while(filename.contains("/"))
    {
        filename.remove(0,filename.indexOf("/")+1);
    }

    qDebug() << filename;
    int no_of_rows = fileSize/SEND_BUF_SIZE + 1;
    int read(0);
    fileBuf = new char[ADD_SIZE + no_of_rows + 1][CHARS];	//Extra row for our special character to be used in conditional statements,here ""
                                            // ADD_SIZE for TO,FROM,SUBJECT,CONTENT-TYPE,CONTENT-TRANSFER-ENCODING,CONETNT-DISPOSITION and \r\n


     QString formatage = "Date: "+QDate::currentDate().toString("ddd, dd MMM yyyy") +" "+
                         QTime::currentTime().toString("hh:mm:ss")+" GMT\r\n";
    strcpy(fileBuf[len++],formatage.toStdString().c_str());

    formatage = "To: "+ mailTo+"\r\n";
    strcpy(fileBuf[len++],formatage.toStdString().c_str());
    buffer_size += strlen(fileBuf[len-1]) + 1;	// 1 for \0

    formatage = "From: " + mailFrom+ "\r\n";
    strcpy(fileBuf[len++],formatage.toStdString().c_str());
    buffer_size += strlen(fileBuf[len-1]) + 1;

    formatage = "Subject: "+mailObject+"\r\n";
    strcpy(fileBuf[len++],formatage.toStdString().c_str());
    buffer_size += strlen(fileBuf[len-1]) + 1;

    strcpy(fileBuf[len++],"--_----------=_10167391557129230\r\n");
    buffer_size += strlen(fileBuf[len-1]) + 1;

    strcpy(fileBuf[len++],"Content-Transfer-Encoding: binary\r\n");
    buffer_size += strlen(fileBuf[len-1]) + 1;

    strcpy(fileBuf[len++],"Content-Type: text/plain\r\n");
    buffer_size += strlen(fileBuf[len-1]) + 1;

    formatage = mailBody+"\r\n";
    strcpy(fileBuf[len++],formatage.toStdString().c_str());
    buffer_size += strlen(fileBuf[len-1]) + 1;

    strcpy(fileBuf[len++],"--_----------=_10167391557129230\r\n");

    formatage = "Content-Type: application/x-msdownload; name=\""+ filename +"\"\r\n";
    strcpy(fileBuf[len++],formatage.toStdString().c_str());
    buffer_size += strlen(fileBuf[len-1]) + 1;

    strcpy(fileBuf[len++],"Content-Transfer-Encoding: base64\r\n");
    buffer_size += strlen(fileBuf[len-1]) + 1;

    formatage = "Content-Disposition: attachment; filename=\""+ filename +"\"\r\n";
    strcpy(fileBuf[len++],formatage.toStdString().c_str());
    buffer_size += strlen(fileBuf[len-1]) + 1;
    strcpy(fileBuf[len++],"\r\n");
    buffer_size += strlen(fileBuf[len-1]) + 1;

    char* temp_buf = new char[SEND_BUF_SIZE + 4];	//taking extra size of 4 bytes
    size_t e_size = ceil(SEND_BUF_SIZE/3)*4 + 4;
    char* encoded_buf = new char[e_size];
    *encoded_buf = 0;

    for (; len < no_of_rows + ADD_SIZE; ++len)
    {
        read = fread(temp_buf,sizeof(char),SEND_BUF_SIZE,hFile);
        temp_buf[read] ='\0';
        base64_encode(temp_buf,encoded_buf);
        strcat(encoded_buf,"\r\n");
        memcpy(fileBuf[len],encoded_buf,strlen(encoded_buf)+1);
                buffer_size += strlen(encoded_buf) + 1;	// 1 for \0
    }
    strcpy(fileBuf[len++],"--_----------=_10167391557129230--\r\n");

    strcpy(fileBuf[len++],".\r\n");
    strcpy(fileBuf[len],"");

    for(int i = 0; i<len; i++)
        qDebug()<< fileBuf[i];
    delete[] temp_buf;
    delete[] encoded_buf;
    return buffer_size;
}

static struct timeval tvnow(void)
{
  struct timeval now;

  /* time() returns the value of time in seconds since the epoch */
  now.tv_sec = (long)time(NULL);
  now.tv_usec = 0;

  return now;
}

static long tvdiff(struct timeval newer, struct timeval older)
{
  return (newer.tv_sec - older.tv_sec) * 1000 +
    (newer.tv_usec - older.tv_usec) / 1000;
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
/*    QFile fic("mail.txt");
    if(fic.open(QIODevice::WriteOnly))
    {
        QTextStream flux(&fic);

        QString formatage = "Date: "+QDate::currentDate().toString("ddd, dd MMM yyyy") +" "+
                            QTime::currentTime().toString("hh:mm:ss")+" GMT\r\n";

        flux << formatage;
        formatage = "From: <"+mailFrom+">\r\n";
        flux << formatage;
        formatage = "To: <"+mailTo+">\r\n";
        flux << formatage;
        formatage = "Subject: "+mailObject+"\r\n";
        flux << formatage;
        flux << "\r\n";
        formatage = mailBody+"\r\n.\r\n";
        flux << formatage;
        flux <<"\r\n";


        FILE* hFile=NULL;
        size_t fileSize(0),len(0),buffer_size(0);

        //opening the file
        hFile = fopen(pieceJointe.toStdString().c_str(),"rb");
        if (hFile == NULL)
        {
            emit("piece jointe  inaccessible");
            return;
        }

        //get file size
        fseek(hFile,0,SEEK_END);
        fileSize = ftell(hFile);
        fseek(hFile,0,SEEK_SET);

        //Checking file size
        if(fileSize > 1*1024)
        {}

        int no_of_rows = fileSize/54 + 1;
        int read(0);

        QString filename = pieceJointe;
        while(filename.contains("/"))
        {
            filename.remove(0,filename.indexOf("/"));
        }
        flux << "Content-Type: application/x-msdownload; name=\""+ filename+ "\"\r\n";

        flux << "Content-Transfer-Encoding: base64\r\n";

        flux << "Content-Disposition: attachment; filename=\"" +filename+ "\"\r\n";

        flux << "\r\n";

        char* temp_buf = new char[SEND_BUF_SIZE + 4];	//taking extra size of 4 bytes
        //size_t e_size = ceil(SEND_BUF_SIZE/3)*4 + 4;
        char* encoded_buf = new char[e_size];
        *encoded_buf = 0;

        for (; len < no_of_rows + ADD_SIZE; ++len)
        {
            read = fread(temp_buf,sizeof(char),54,hFile);
            temp_buf[read] ='\0';
            base64_encode(temp_buf,encoded_buf);
            strcat(encoded_buf,"\r\n");
            memcpy(fileBuf[len],encoded_buf,strlen(encoded_buf)+1);
                    buffer_size += strlen(encoded_buf) + 1;	// 1 for \0

        }
        flux << "";

        fic.close();
    }*/
}

void TraitementThread::envoyerMail()
{
    emit sendTraitementEnCours(QString("Chargement de la pièce jointe"));
    FILE *file_debug=NULL;
    QString path = QDir::currentPath()+"/toto.txt";
    file_debug = fopen(path.toStdString().c_str(), "a+");   //open the specified file on local host

    //reformater();
    int still_running = 1;
    struct timeval mp_start;

    FILE *hd_src;
    path = QDir::currentPath()+"/mail.txt";
    hd_src = fopen(path.toStdString().c_str(), "r");

    struct curl_slist *recipients = NULL;

    struct fileBuf_upload_status file_upload_ctx;
    size_t file_size(0);

    file_upload_ctx.lines_read = 0;

    curl = curl_easy_init();
    mcurl = curl_multi_init();
    file_size = read_file();

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
        /*
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
        curl_easy_setopt(curl, CURLOPT_READDATA, hd_src);*/
        curl_easy_setopt(curl, CURLOPT_INFILESIZE, file_size);
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, fileBuf_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &file_upload_ctx);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        if(configServeur->getLogActions())
        {
            curl_easy_setopt(curl, CURLOPT_STDERR,file_debug);
        }

        /* Send the message */

        //res = curl_easy_perform(curl);
        /* Tell the multi stack about our easy handle */
          curl_multi_add_handle(mcurl, curl);

          /* Record the start time which we can use later */
          mp_start = tvnow();

          /* We start some action by calling perform right away */
          curl_multi_perform(mcurl, &still_running);

          while(still_running) {
            struct timeval timeout;
            fd_set fdread;
            fd_set fdwrite;
            fd_set fdexcep;
            int maxfd = -1;
            int rc;
            CURLMcode mc; /* curl_multi_fdset() return code */

            long curl_timeo = -1;

            /* Initialise the file descriptors */
            FD_ZERO(&fdread);
            FD_ZERO(&fdwrite);
            FD_ZERO(&fdexcep);

            /* Set a suitable timeout to play around with */
            timeout.tv_sec = 1;
            timeout.tv_usec = 0;

            curl_multi_timeout(mcurl, &curl_timeo);
            if(curl_timeo >= 0) {
              timeout.tv_sec = curl_timeo / 1000;
              if(timeout.tv_sec > 1)
                timeout.tv_sec = 1;
              else
                timeout.tv_usec = (curl_timeo % 1000) * 1000;
            }

            /* get file descriptors from the transfers */
            mc = curl_multi_fdset(mcurl, &fdread, &fdwrite, &fdexcep, &maxfd);

            if(mc != CURLM_OK)
            {
              fprintf(stderr, "curl_multi_fdset() failed, code %d.\n", mc);
              break;
            }

            if(maxfd == -1)
            {
                #ifdef _WIN32
                      Sleep(100);
                      rc = 0;
                #else
                      /* Portable sleep for platforms other than Windows. */
                      struct timeval wait = { 0, 100 * 1000 }; /* 100ms */
                      rc = select(0, NULL, NULL, NULL, &wait);
                #endif
            }
            else {
             // rc = select(maxfd+1, &fdread, &fdwrite, &fdexcep, &timeout);
            }

            if(tvdiff(tvnow(), mp_start) > MULTI_PERFORM_HANG_TIMEOUT) {
              fprintf(stderr,
                      "ABORTING: Since it seems that we would have run forever.\n");
              break;
            }

            switch(rc) {
            case -1:  /* select error */
              break;
            case 0:   /* timeout */
            default:  /* action */
              curl_multi_perform(mcurl, &still_running);
              break;
            }
          }

        /* Check for errors */
        if(res != CURLE_OK)
        {
            QString err = QString("curl_easy_perform() failed: %1\n").arg(curl_easy_strerror(res));
            emit erreur(err);
        }

      /* Always cleanup */
      curl_slist_free_all(recipients);
      curl_easy_cleanup(curl);

      // fermeture des fichiers
      fclose(file_debug);
      fclose(hd_src);

      // log
      if(configServeur->getLogActions())
          ecrirelog(1);

      delete[] fileBuf;
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
    PJ = piece;
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
    contenue += from + subject + to ;
    toto.clear();
}


