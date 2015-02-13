#include "chat.h"
#include "ui_chat.h"

Chat::Chat(QWidget *parent) : QMainWindow(parent), ui(new Ui::Chat) {
    ui->setupUi(this);

    socket = new QUdpSocket(this);                              //new socket for recieving messages
    socket->bind(7777);                                         //bind at empty port
    connect(socket, SIGNAL(readyRead()), this, SLOT(read()));   //connecting
}

Chat::~Chat() {
    delete ui;
}

void Chat::addUser(QString name) {  //adding new user for current client
    names.push_back(name);
    ui->textBrowser_2->append(name);
    ui->textBrowser->append(name + " has joined");
    count++;
}

void Chat::sendHello(QString name) {   //send name of new user to all participants
    QByteArray data;
    data.append(name);
    socket->writeDatagram(data.data(), data.size(), QHostAddress::Broadcast, 7777);
}

void Chat::on_pushButton_clicked() {  //sending message
    QDateTime time = QDateTime::currentDateTime();
    if (ui->textEdit->toPlainText() == "" || ui->textEdit->toPlainText() == NULL)
        return;
    QString str = "[" + myName + "][" + time.toString() + "]: " + ui->textEdit->toPlainText();
    ui->textEdit->setText("");
    QByteArray data;
    data.append(str);
    socket->writeDatagram(data.data(), data.size(), QHostAddress::Broadcast, 7777);
}

void Chat::read() {  //reading from socket
    QByteArray data;
    while (socket->hasPendingDatagrams()) {
        data.resize(socket->pendingDatagramSize());
        socket->readDatagram(data.data(), data.size());
        QString msg = QString(data);
        if (msg.at(0) != '[') {
            addUser(msg);                     //for new users
        }
        else {
            ui->textBrowser->append(msg);     //for simple message
        }
    }
}
