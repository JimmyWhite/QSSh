#include "form.h"
#include "ui_form.h"
#include "mainwindow.h"
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(400,300);
    ui->label_2->setAlignment(Qt::AlignCenter);
    ui->label_3->setAlignment(Qt::AlignCenter);
    ui->label_4->setAlignment(Qt::AlignCenter);
    ui->lineEdit_3->setEchoMode(QLineEdit::Password);
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{
    m = new MainWindow();
    m->show();
    this->hide();
}
