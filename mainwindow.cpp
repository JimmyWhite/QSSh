#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qwidget.h"
#include "myssh.h"
#include "head/sshconnection.h"
#include <QRegExp>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(650,500);
    ui->setupUi(this);
    QSsh::SshConnectionParameters param;
    param.host="192.168.223.129";
    param.port=22;
    param.userName="root";
    param.password="1314512";
    param.authenticationType = QSsh::SshConnectionParameters::AuthenticationTypeTryAllPasswordBasedMethods;
    param.timeout = 2000;
    myssh = new MySsh(param);
    connect(myssh,SIGNAL(showData(int,QByteArray)),this,SLOT(showData(int,QByteArray)));
    connect(this,SIGNAL(command(QByteArray)),myssh,SLOT(Send(QByteArray)));
    myssh->start();
}


void MainWindow::showData(int type,QByteArray data)
{
    if (type==1)
    {
    ui->tableWidget_5->resizeRowsToContents();
    ui->tableWidget_5->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_5->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QString version;
    QString cpu;
    QString ram;
    QString disk;
    QString time;
    if (data.indexOf("uptaime")!=-1)
    {
    version = data.mid(0,data.indexOf("\r\n"));
    }
    else
    {
      int index = data.indexOf("uptime");
      data = data.mid(index+10,-1);
      version = data.mid(0,data.indexOf("\r\n"));
    }
    data =data.mid(data.indexOf("\r\n")+1,-1);
    data =data.mid(data.indexOf("\r\n")+2,-1);
    cpu = data.mid(12,data.indexOf("\r\n")-12);
    data = data.mid(data.indexOf("MemTotal"),-1);
    ram = data.mid(17,data.indexOf("\r\n")-17);
    data = data.mid(data.indexOf("Disk /dev/sda"),-1);
    disk = data.mid(15,data.indexOf(",")-15);
    data = data.mid(data.indexOf("identifier"),-1);
    data = data.mid(data.indexOf("\r\n")+2,-1);
    time = data.mid(0,data.indexOf(","));
    QTableWidgetItem *pversion = new QTableWidgetItem(version);
    QTableWidgetItem *pcpu = new QTableWidgetItem(cpu);
    QTableWidgetItem *pram = new QTableWidgetItem(ram);
    QTableWidgetItem *pdisk = new QTableWidgetItem(disk);
    QTableWidgetItem *ptime = new QTableWidgetItem(time);
    pversion->setTextAlignment(Qt::AlignCenter);
    pcpu->setTextAlignment(Qt::AlignCenter);
    pram->setTextAlignment(Qt::AlignCenter);
    pdisk->setTextAlignment(Qt::AlignCenter);
    ptime->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_5->setItem(0,0,pversion);
    ui->tableWidget_5->setItem(1,0,pcpu);
    ui->tableWidget_5->setItem(2,0,pram);
    ui->tableWidget_5->setItem(3,0,pdisk);
    ui->tableWidget_5->setItem(4,0,ptime);
    emit command("ifconfig\r\n");
    }
   if (type==2)
   {
    ui->tableWidget_4->resizeRowsToContents();
    ui->tableWidget_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_4->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QString name;
    QString size;
    QString time1;
    QString time2;
    QString time3;
    name = "/etc/passwd";
    int index = data.indexOf("大小：")+9;
    while (data.at(index)!=' ')
    {
        size = size +data.at(index);
        index ++;
    }
    index = data.indexOf("最近访问")+15;
    data = data.mid(index, -1);
    time1 = data.mid(0,data.indexOf("\r\n"));
    index = data.indexOf("最近更改")+15;
    data = data.mid(index,-1);
    time2 = data.mid(0,data.indexOf("\r\n"));
    index = data.indexOf("最近改动")+15;
    data = data.mid(index,-1);
    time3 = data.mid(0,data.indexOf("\r\n"));
    QTableWidgetItem *pname = new QTableWidgetItem(name);
    QTableWidgetItem *psize = new QTableWidgetItem(size);
    QTableWidgetItem *ptime1 = new QTableWidgetItem(time1);
    QTableWidgetItem *ptime2 = new QTableWidgetItem(time2);
    QTableWidgetItem *ptime3 = new QTableWidgetItem(time3);
    pname->setTextAlignment(Qt::AlignCenter);
    psize->setTextAlignment(Qt::AlignCenter);
    ptime1->setTextAlignment(Qt::AlignCenter);
    ptime2->setTextAlignment(Qt::AlignCenter);
    ptime3->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_4->setItem(0,0,pname);
    ui->tableWidget_4->setItem(1,0,psize);
    ui->tableWidget_4->setItem(2,0,ptime1);
    ui->tableWidget_4->setItem(3,0,ptime2);
    ui->tableWidget_4->setItem(4,0,ptime3);
    emit command("iptables -L -n\r\n");
   }
    if (type==3)
    {
    ui->tableWidget_3->resizeRowsToContents();
    ui->tableWidget_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_3->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    data =data.mid(data.indexOf("\r\n")+2,-1);
    QString name;
    QString ip;
    QString mask;
    QString broadcast;
    QString mac;
    name = data.mid(0,data.indexOf(":"));
    data =data.mid(data.indexOf("inet")+5);
    ip = data.mid(0,data.indexOf(" "));
    data =data.mid(data.indexOf("netmask")+8);
    mask = data.mid(0,data.indexOf(" "));
    data = data.mid(data.indexOf("broadcast")+10);
    broadcast = data.mid(0,data.indexOf("\r\n"));
    data = data.mid(data.indexOf("ether")+6);
    mac = data.mid(0,data.indexOf(" "));
    QTableWidgetItem *pname = new QTableWidgetItem(name);
    QTableWidgetItem *pip = new QTableWidgetItem(ip);
    QTableWidgetItem *pmask = new QTableWidgetItem(mask);
    QTableWidgetItem *pbroadcast = new QTableWidgetItem(broadcast);
    QTableWidgetItem *pmac = new QTableWidgetItem(mac);
    pname->setTextAlignment(Qt::AlignCenter);
    pip->setTextAlignment(Qt::AlignCenter);
    pmask->setTextAlignment(Qt::AlignCenter);
    pbroadcast->setTextAlignment(Qt::AlignCenter);
    pmac->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_3->setItem(0,0,pname);
    ui->tableWidget_3->setItem(1,0,pip);
    ui->tableWidget_3->setItem(2,0,pmask);
    ui->tableWidget_3->setItem(3,0,pbroadcast);
    ui->tableWidget_3->setItem(4,0,pmac);
    emit command("stat /etc/passwd\r\n");
    }
   if (type==4)
   {
     ui->tableWidget_2->resizeColumnsToContents();
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    int columns = 1;
    data = data.mid(data.indexOf("\r\n")+1,-1);
    data = data.mid(data.indexOf("\r\n")+1,-1);
    while (data.indexOf(".")!=-1)
    {
    QString user = data.mid(0,data.indexOf(" "));
    QString pattern("([01][0-9]|2[0-3]):[0-5][0-9](:[0-5][0-9])?");
    QRegExp rx(pattern);
    rx.indexIn(data);
    QString time = rx.cap(0);
    rx.setPattern("([0-9][0-9][0-9]|[0-9][0-9][0-9][0-9])");
    rx.indexIn(data);
    QString pid = rx.cap(0);
    rx.setPattern("[0-9]+[.][0-9]+");
    rx.indexIn(data);
    QString cpu = rx.cap(0);
    data =data.mid(data.indexOf('.')+1,-1);
    rx.setPattern("[0-9]+[.][0-9]+");
    rx.indexIn(data);
    QString mem = rx.cap(0);
    ui->tableWidget_2->setItem(columns,0,new QTableWidgetItem(pid));
    ui->tableWidget_2->setItem(columns,1,new QTableWidgetItem(cpu));
    ui->tableWidget_2->setItem(columns,2,new QTableWidgetItem(mem));
    ui->tableWidget_2->setItem(columns,3,new QTableWidgetItem(time));
    ui->tableWidget_2->setItem(columns,4,new QTableWidgetItem(user));
    columns++;
    data = data.mid(data.indexOf("\r\n")+1,-1);
    }
   }
   if (type==5)
   {
       qDebug()<<data;
   QString dict[10000];
    dict[22]="ssh";
    dict[3306]="mysql";
    dict[1521]="oracle";
    dict[80]="http";
    dict[8080]="http-alt";
    dict[443]="https";
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    int columns =1;
    data = data.mid(data.indexOf("\r\n")+1,-1);
    data = data.mid(data.indexOf("\r\n")+1,-1);
    data = data.mid(data.indexOf("\r\n")+1,-1);
    int len = data.indexOf("FORWARD");
    data =data.mid(0,len);
    while (data.indexOf("dpt:")!=-1)
    {
       QString pattern("((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])[\\.]){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])");
       QRegExp rx(pattern);
       rx.indexIn(data);
       int len1 = data.indexOf("dpt:");
       int len2 = data.indexOf("\r\n");
       QString port = data.mid(len1+4,len2-len1-4);
       ui->tableWidget->setItem(columns,0,new QTableWidgetItem(port));
       if (data.indexOf("ACCEPT")!=-1)
       ui->tableWidget->setItem(columns,1,new QTableWidgetItem("开放"));
       else
       ui->tableWidget->setItem(columns,1,new QTableWidgetItem("关闭"));
       if (data.indexOf("tcp")!=-1)
       ui->tableWidget->setItem(columns,2,new QTableWidgetItem("TCP"));
       else
       ui->tableWidget->setItem(columns,2,new QTableWidgetItem("UDP"));
       ui->tableWidget->setItem(columns,3,new QTableWidgetItem(dict[port.toInt()]));
       ui->tableWidget->setItem(columns,4,new QTableWidgetItem(rx.cap(0)));
       columns++;
       data = data.mid(len2+1);
    }
    emit command("ps au\r\n");
   }
}
MainWindow::~MainWindow()
{
    delete ui;
}
