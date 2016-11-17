#include "mainwindow.h"
#include "form.h"
#include <QApplication>
#include <myssh.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Form m;
    m.show();
 /*   QSsh::SshConnectionParameters param;
    param.host="192.168.223.129";
    param.port=22;
    param.userName="root";
    param.password="1314512";
    param.authenticationType = QSsh::SshConnectionParameters::AuthenticationTypeTryAllPasswordBasedMethods;
    param.timeout = 2000;
    MySsh myssh(param);*/
    return a.exec();
}
