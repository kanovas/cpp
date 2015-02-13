#include "name.h"
#include "ui_name.h"

Name::Name(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Name)
{
    ui->setupUi(this);
}

Name::~Name()
{
    delete ui;
}

void Name::on_buttonBox_accepted()
{
    name = ui->lineEdit->text();
    if (name == "") {
        name = "anonymous";
    }
    mainWindow->show();
    mainWindow->sendHello(name);
    mainWindow->myName = name;
    this->close();
}

void Name::setKostyl(Chat *kostyl) {
    mainWindow = kostyl;
}
