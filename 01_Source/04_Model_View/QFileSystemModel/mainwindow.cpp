#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QFileSystemModel(this);
    model ->setRootPath(QDir::currentPath());//设置根节点
    ui->treeView->setModel(model);
    ui->listView->setModel(model);
    ui->tableView->setModel(model);

    connect(ui->treeView,&QTreeView::clicked,this,[=](QModelIndex model)
    {
        ui->listView->setRootIndex(model);
        ui->tableView->setRootIndex(model);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    ui->chkIsDir->setChecked(true);
    ui->chkIsDir->setChecked(model->isDir(index));
        ui->chkIsDir->setChecked(false);

    ui->LabPath->setText(model->filePath(index));
    ui->LabType->setText(model->type(index));
    ui->LabFileName->setText(model->fileName(index));

    int sz=model->size(index)/1024;
    if(sz<1024)
    {
        ui->LabFileSize->setText(QString("%1 KB").arg(sz));
    }else
    {
        ui->LabFileSize->setText(QString::asprintf("%.1f MB",sz/1024.0));
    }
}

