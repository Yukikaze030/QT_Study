#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString str=ui->m_lineEdit_Quantity->text();//获取数量
    int num = str.toInt();

    str = ui->m_lineEdit_Univalent->text();
    float quantity = str.toFloat();
    float price = num * quantity;
    str = str.sprintf("%.2f",price);
    ui->m_lineEdit_Price->setText(str);
}




void MainWindow::on_m_pushButton_Decimal_clicked()
{
    QString str=ui->m_lineEdit_Decimal->text();
    ui->m_lineEdit_Binary->setText(str.setNum(str.toInt(nullptr,10),2));//str.setNum(10); "str == 10" true!
    str=ui->m_lineEdit_Decimal->text();
    ui->m_lineEdit_Hexadecimal->setText(str.setNum(str.toInt(nullptr,10),16).toUpper());
}


void MainWindow::on_m_pushButton_Binary_clicked()
{
    QString str=ui->m_lineEdit_Binary->text();
    ui->m_lineEdit_Decimal->setText(str.setNum(str.toInt(nullptr,2),10));//str.setNum(10); "str == 10" true!
    str=ui->m_lineEdit_Decimal->text();
    ui->m_lineEdit_Hexadecimal->setText(str.setNum(str.toInt(nullptr,2),16).toUpper());
}


void MainWindow::on_m_pushButton_Hexadecimal_clicked()
{
    QString str=ui->m_lineEdit_Hexadecimal->text();
    ui->m_lineEdit_Binary->setText(str.setNum(str.toInt(nullptr,16),2));//str.setNum(10); "str == 10" true!
    str=ui->m_lineEdit_Hexadecimal->text();
    ui->m_lineEdit_Decimal->setText(str.setNum(str.toInt(nullptr,16),10).toUpper());
}

