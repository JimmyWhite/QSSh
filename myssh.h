#ifndef MYSSH_H
#define MYSSH_H

#include <QObject>
#include<QSharedPointer>
#include <head/sshconnection.h>
#include <head/sshremoteprocess.h>

class MySsh : public QObject
{
    Q_OBJECT
public:
    explicit MySsh(QSsh::SshConnectionParameters &param,QObject *parent=0);
    ~MySsh();
    void start();
    int count;
    QSsh::SshConnection *connection;
    QSharedPointer<QSsh::SshRemoteProcess> shell;
signals:
    void ready();
    void showData(int type,QByteArray data);
public slots:
    void dealConnected();
    void dealData();
    void Send(QByteArray command);
    void dealError();

};

#endif // MYSSH_H
