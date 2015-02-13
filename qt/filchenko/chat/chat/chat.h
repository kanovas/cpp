#ifndef CHAT_H
#define CHAT_H

#include <QMainWindow>
#include <QString>
#include <QUdpSocket>
#include <QDateTime>

namespace Ui {
class Chat;
}

class Chat : public QMainWindow
{
    Q_OBJECT

public:
    explicit Chat(QWidget *parent = 0);
    ~Chat();
    void sendHello(QString name);
    void addUser(QString name);
    QUdpSocket * socket;
    QString myName;

private slots:
    void on_pushButton_clicked();
    void read();

private:
    Ui::Chat *ui;
    QVector<QString> names;
    int count;
};

#endif // CHAT_H
