#include "mainwindow.h"
#include "./ui_mainwindow.h"

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

void MainWindow::on_m_pushButton_Append_clicked()
{
    QString str1 = ui->m_lineEdit_str1->text();
    QString str2 = ui->m_lineEdit_str2->text();
    QString str3 = str1.append(str2);
    ui->m_lineEdit_results->setText(str3);
}


void MainWindow::on_m_pushButton_Prepend_clicked()
{
    QString str1 = ui->m_lineEdit_str1->text();
    QString str2 = ui->m_lineEdit_str2->text();
    QString str3 = str1.prepend(str2);
    ui->m_lineEdit_results->setText(str3);
}


void MainWindow::on_m_pushButton_toUpper_clicked()
{
    QString str1 = ui->m_lineEdit_str1->text();
    QString str3 = str1.toUpper();
    ui->m_lineEdit_results->setText(str3);
}


void MainWindow::on_m_pushButton_toLower_clicked()
{
    QString str1 = ui->m_lineEdit_str1->text();
    QString str3 = str1.toLower();
    ui->m_lineEdit_results->setText(str3);
}


void MainWindow::on_m_pushButton_left_clicked()
{
    QString str1 = ui->m_lineEdit_str1->text();
    QString str3 = str1.left(1);
    ui->m_lineEdit_results->setText(str3);
}

