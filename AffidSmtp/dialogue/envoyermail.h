#ifndef ENVOYERMAIL_H
#define ENVOYERMAIL_H

#include <QDialog>

namespace Ui {
class EnvoyerMail;
}

class EnvoyerMail : public QDialog
{
    Q_OBJECT

public:
    explicit EnvoyerMail(QWidget *parent = 0);
    ~EnvoyerMail();
    void showEvent(QShowEvent *event);

private:
    Ui::EnvoyerMail *ui;

signals:
    void envoyerParams(QString to, QString subject, QString body,QString piece);

private slots:
    void valider();
    void parcourir();
};

#endif // ENVOYERMAIL_H
