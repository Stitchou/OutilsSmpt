#include "mainwindow.h"
#include "ui_mainwindow.h"

// importation des classes
#include "./dialogue/configurationsesamvitale.h"
#include "./curl/curlinterprete.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Affid Smtp");

    // pointeur de la classe de configuration
    configure = new ConfigurationSesamVitale;


    // tuilisation de curl librarie
    interpreteCurl = new CurlInterprete;

    connect(ui->lister, SIGNAL(clicked()), this, SLOT(listerMails()));
    connect(ui->envoyer, SIGNAL(clicked()), this, SLOT(envoyerMail()));
    connect(ui->configurer, SIGNAL(clicked()), this, SLOT(configurerSmtp()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::listerMails()
{
    interpreteCurl->listerMail();
}

void MainWindow::envoyerMail()
{
    interpreteCurl->envoyerNouveauMail();
}

void MainWindow::configurerSmtp()
{
    configure->show();
}
