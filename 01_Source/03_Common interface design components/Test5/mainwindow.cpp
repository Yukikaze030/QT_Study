#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextBlock>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textBrowser->setContextMenuPolicy(Qt::CustomContextMenu);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_m_pushButton_ResetList_clicked()
{
    QIcon icon;
    icon.addFile(":/new/prefix1/image1");
    ui->comboBox->clear();
    for(int i=0;i<20;i++)
    {
        ui->comboBox->addItem(icon,QString::asprintf("Item %d",i));
    }

}


void MainWindow::on_m_pushButton_ResetCity_clicked()
{
    QMap<QString,int> City_Zone;
    City_Zone.insert("北京",010);
    City_Zone.insert("上海",021);
    City_Zone.insert("天津",022);
    ui->m_comboBox_City->clear();
    foreach (const QString &str, City_Zone.keys()) {
        ui->m_comboBox_City->addItem(str,City_Zone.value(str));
    }

}


void MainWindow::on_m_pushButton_TextAddComboBox_clicked()
{
    QTextDocument* doc = ui->textBrowser->document();
    int cnt=doc->blockCount();
    QIcon icon{":/new/prefix1/image1"};
    ui->comboBox->clear();
    for(int i=0;i<cnt;i++)
    {
        QTextBlock textLine = doc->findBlockByNumber(i);
        QString str=textLine.text();
        ui->comboBox->addItem(icon,str);
    }
}


void MainWindow::on_m_checkBox_ReadOnly_stateChanged(int arg1)
{
    ui->textBrowser->setReadOnly(arg1);
}



void MainWindow::on_textBrowser_customContextMenuRequested(const QPoint &pos)
{
//    QMenu* menu=ui->textBrowser->createStandardContextMenu();
//    menu->clear();
//    menu->addAction("1");
    QMenu* menu = new QMenu(ui->textBrowser);
    menu->addAction("1");
    menu->exec(QCursor::pos());
}

