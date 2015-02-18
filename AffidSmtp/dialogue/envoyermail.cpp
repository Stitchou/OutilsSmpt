#include "envoyermail.h"
#include "ui_envoyermail.h"

EnvoyerMail::EnvoyerMail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnvoyerMail)
{
    ui->setupUi(this);
    connect(ui->annuler,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->valider,SIGNAL(clicked()),this,SLOT(valider()));
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
    emit envoyerParams(ui->destinataire->text(),ui->sujet->text(),ui->body->toPlainText());
    this->close();
}
