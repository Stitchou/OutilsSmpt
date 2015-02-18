/********************************************************************************
** Form generated from reading UI file 'progression.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGRESSION_H
#define UI_PROGRESSION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>

QT_BEGIN_NAMESPACE

class Ui_Progression
{
public:
    QProgressBar *progressBar;
    QLabel *label;

    void setupUi(QDialog *Progression)
    {
        if (Progression->objectName().isEmpty())
            Progression->setObjectName(QStringLiteral("Progression"));
        Progression->resize(271, 90);
        progressBar = new QProgressBar(Progression);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(20, 50, 231, 23));
        progressBar->setValue(0);
        label = new QLabel(Progression);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 231, 20));

        retranslateUi(Progression);

        QMetaObject::connectSlotsByName(Progression);
    } // setupUi

    void retranslateUi(QDialog *Progression)
    {
        Progression->setWindowTitle(QApplication::translate("Progression", "Dialog", 0));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Progression: public Ui_Progression {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGRESSION_H
