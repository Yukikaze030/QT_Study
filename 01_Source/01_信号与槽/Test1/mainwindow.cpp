#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->m_pbtTest,&QPushButton::clicked,this,[=](){
        QPushButton *pPbt = qobject_cast<QPushButton*>(sender());//QObject::sender()获取发送信号对象指针
        if(pPbt->text() == "Test1")
        {
            pPbt->setText("Test2");
        }else
        {
            pPbt->setText("Test1");
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

