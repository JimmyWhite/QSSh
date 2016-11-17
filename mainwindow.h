#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "head/sshconnection.h"
#include "head/sshremoteprocess.h"
#include <QSharedPointer>
#include <QMainWindow>
#include <myssh.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    MySsh *myssh;
public slots:
    void showData(int type,QByteArray data);
signals:
    void command(QByteArray cmd);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
