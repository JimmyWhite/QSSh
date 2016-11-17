#include "myssh.h"
#include "head/sshconnection.h"
#include "head/sshremoteprocess.h"
#include "qdebug.h"
#include <cstdlib>
using namespace QSsh;
MySsh::MySsh(SshConnectionParameters &param,QObject *parent) : QObject(parent)
{
    count = 0;
    connection = new SshConnection(param);
    connect(this,SIGNAL(ready()),this,SLOT(Send()));
    connect(connection,SIGNAL(connected()),SLOT(dealConnected()));
    connect(connection,SIGNAL(error(QSsh::SshError)),this,SLOT(dealError()));
}

void MySsh::start()
{
    connection->connectToHost();

}
void MySsh::dealError()
{
    qDebug()<<connection->errorString();

}
void MySsh::Send(QByteArray command)
{
    qDebug()<<command;
    shell->write(command);

}
void MySsh::dealConnected()
{
    shell = connection->createRemoteShell();
    connect(shell.data(),SIGNAL(readyReadStandardOutput()),SLOT(dealData()));
    connect(shell.data(),SIGNAL(closed(int)),SLOT(dealClose(int)));
    shell->start();
}

void MySsh::dealData()
{
    QByteArray data = shell->readAllStandardOutput().data();
    if (count==0)
    {
        shell->write("uname -r ; cat /proc/cpuinfo | grep model ; cat /proc/meminfo | grep MemTotal ; fdisk -l | grep Disk; uptime ;\r\n");
        count++;
    }

    if (data.indexOf("Disk")!=-1)
    {
        emit showData(1,data);
    }
    if (data.indexOf("passwd")!=-1)
    {
        emit showData(2,data);
    }
    if (data.indexOf("netmask")!=-1)
    {
        emit showData(3,data);
    }
    if (data.indexOf("COMMAND")!=-1)
    {
        emit showData(4,data);
    }
    if (data.indexOf("Chain")!=-1)
    {
        emit showData(5,data);
    }
    count++;

}

MySsh::~MySsh()
{

}

