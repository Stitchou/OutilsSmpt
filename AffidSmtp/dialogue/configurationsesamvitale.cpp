#include "configurationsesamvitale.h"
#include "ui_configurationsesamvitale.h"

ConfigurationSesamVitale::ConfigurationSesamVitale(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationSesamVitale)
{
    ui->setupUi(this);
    this->setWindowTitle("Configuration du Réseau Sesam-Vitale");
}

ConfigurationSesamVitale::~ConfigurationSesamVitale()
{
    delete ui;
}

