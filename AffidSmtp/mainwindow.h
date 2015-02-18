#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class ConfigurationSesamVitale;
class CurlInterprete;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ConfigurationSesamVitale *configure;
    CurlInterprete * interpreteCurl;

private slots:
    void listerMails();
    void envoyerMail();
    void configurerSmtp();
};

#endif // MAINWINDOW_H
