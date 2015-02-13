#ifndef NAME_H
#define NAME_H

#include <QtWidgets/QDialog>
#include <QString>
#include "chat.h"

namespace Ui {
class Name;
}

class Name : public QDialog
{
    Q_OBJECT

public:
    explicit Name(QWidget *parent = 0);
    ~Name();
    void setKostyl(Chat *kostyl);
    QString name;


private slots:
    void on_buttonBox_accepted();

private:
    Ui::Name *ui;
    Chat *mainWindow;
};

#endif // NAME_H
