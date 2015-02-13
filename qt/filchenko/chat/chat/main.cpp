#include "chat.h"
#include "name.h"
#include <QApplication>
#include <QUdpSocket>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Chat window;
    Name askName;
    askName.setKostyl(&window);
    askName.show();

   return a.exec();
}

