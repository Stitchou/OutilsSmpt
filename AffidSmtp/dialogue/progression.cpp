#include "progression.h"
#include "ui_progression.h"

Progression::Progression(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Progression)
{
    ui->setupUi(this);
    ui->progressBar->setMaximum(0);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}

Progression::~Progression()
{
    delete ui;
}

void Progression::setMessage(QString message)
{
    ui->label->setText(message);
}
