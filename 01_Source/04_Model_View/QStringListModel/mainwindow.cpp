#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList theStrList;
    theStrList<<"北京"<<"上海"<<"天津"<<"河北";
    theModel=new QStringListModel(this);
    theModel->setStringList(theStrList);
    ui->listView->setModel(theModel);
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::SelectedClicked);//设置双击可编辑
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnListAppend_clicked()
{
    theModel->insertRow(theModel->rowCount());
    QModelIndex index = theModel->index(theModel->rowCount()-1);
    theModel->setData(index,"new item",Qt::DisplayRole);
    ui->listView->setCurrentIndex(index);
}


void MainWindow::on_btnListInsert_clicked()
{
    QModelIndex index = ui->listView->currentIndex();
    theModel->insertRow(index.row());
    theModel->setData(index,"inserted item",Qt::DisplayRole);
    ui->listView->setCurrentIndex(index);
}


void MainWindow::on_btnListDelete_clicked()
{
    QModelIndex index = ui->listView->currentIndex();
    theModel->removeRow(index.row());
}


void MainWindow::on_btnTextImport_clicked()
{
    QStringList strList = theModel->stringList();
    ui->plainTextEdit->clear();
    for(auto string : strList)
    {
        ui->plainTextEdit->append(string);
    }
}


void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    ui->LabInfo->setText(QString::asprintf("当前条目:row=%d, column=%d",index.row(),index.column()));
}

