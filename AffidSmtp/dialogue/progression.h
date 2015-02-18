#ifndef PROGRESSION_H
#define PROGRESSION_H

#include <QDialog>

namespace Ui {
class Progression;
}

class Progression : public QDialog
{
    Q_OBJECT

public:
    explicit Progression(QWidget *parent = 0);
    ~Progression();

private:
    Ui::Progression *ui;

private slots:
    void setMessage(QString message);
};

#endif // PROGRESSION_H
