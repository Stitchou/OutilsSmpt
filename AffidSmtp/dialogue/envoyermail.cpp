#include "envoyermail.h"
#include "ui_envoyermail.h"
#include <QFileDialog>
#include <QFileInfo>

EnvoyerMail::EnvoyerMail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnvoyerMail)
{
    ui->setupUi(this);
    connect(ui->annuler,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->valider,SIGNAL(clicked()),this,SLOT(valider()));
    connect(ui->parcourir,SIGNAL(clicked()),this,SLOT(parcourir()));
}

EnvoyerMail::~EnvoyerMail()
{
    delete ui;
}

void EnvoyerMail::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    ui->destinataire->clear();
    ui->sujet->clear();
    ui->body->clear();
}

void EnvoyerMail::valider()
{
    emit envoyerParams(ui->destinataire->text(),ui->sujet->text()
                       ,ui->body->toPlainText(),ui->piece->text());
    this->close();
}

void EnvoyerMail::parcourir()
{
    QString files;
    files = QFileDialog::getOpenFileName (this,"Emplacement",QDir::currentPath());

    if ( ! files.isEmpty() )
    {
        QFileInfo informations(files);
        ui->piece->setText(informations.filePath());
    }
}

