/********************************************************************************
** Form generated from reading UI file 'name.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NAME_H
#define UI_NAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_Name
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit;

    void setupUi(QDialog *Name)
    {
        if (Name->objectName().isEmpty())
            Name->setObjectName(QStringLiteral("Name"));
        Name->resize(400, 114);
        buttonBox = new QDialogButtonBox(Name);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 70, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEdit = new QLineEdit(Name);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(20, 30, 361, 22));
        lineEdit->setCursor(QCursor(Qt::ArrowCursor));

        retranslateUi(Name);
        QObject::connect(buttonBox, SIGNAL(accepted()), Name, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Name, SLOT(reject()));

        QMetaObject::connectSlotsByName(Name);
    } // setupUi

    void retranslateUi(QDialog *Name)
    {
        Name->setWindowTitle(QApplication::translate("Name", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class Name: public Ui_Name {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NAME_H
