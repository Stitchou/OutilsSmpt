#ifndef CONFIGURATIONSESAMVITALE_H
#define CONFIGURATIONSESAMVITALE_H

#include <QDialog>

namespace Ui {
class ConfigurationSesamVitale;
}

class ConfigurationSesamVitale : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigurationSesamVitale(QWidget *parent = 0);
    ~ConfigurationSesamVitale();

private:
    Ui::ConfigurationSesamVitale *ui;
};

#endif // CONFIGURATIONSESAMVITALE_H
