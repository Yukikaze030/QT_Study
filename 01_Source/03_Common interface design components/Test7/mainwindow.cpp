#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    LabFileName = new QLabel("");
    ui->statusBar->addWidget(LabFileName);
    this->setCentralWidget(ui->scrollArea);
    iniTree();//初始化树
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::iniTree()
{
    QString dataStr="";
    ui->treeFiles->clear();
    QIcon icon;
    icon.addFile(":/ico/ico/15.ico");

    QTreeWidgetItem* item=new QTreeWidgetItem(MainWindow::itTopItem);//创建节点
    item->setIcon(MainWindow::colItem,icon);//第一列图标
    item->setText(MainWindow::colItem,"图片文件");//第一列文字
    item->setText(MainWindow::colItemType,"type=itTopItem");//第二列Q_UNUSED123
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsAutoTristate);
    item->setCheckState(colItem,Qt::Checked);

    item->setData(MainWindow::colItem,Qt::UserRole,QVariant(dataStr));
    ui->treeFiles->addTopLevelItem(item);

}


void MainWindow::on_treeFiles_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(previous);
    if(current == nullptr)
    {
        return;
    }
    int var = current->type();
    switch(var)
    {
    case itTopItem://顶层节点
        ui->actionAddFolder->setEnabled(true);
        ui->actionAddFiles->setEnabled(true);
        ui->actionDeleteItem->setEnabled(false);
        break;

    case itGroupItem://组节点
        ui->actionAddFolder->setEnabled(true);
        ui->actionAddFiles->setEnabled(true);
        ui->actionDeleteItem->setEnabled(true);
        break;

    case itImageItem://图片文件节点
        ui->actionAddFolder->setEnabled(false);//图片节点下不能添加目录节点
        ui->actionAddFiles->setEnabled(true);
        ui->actionDeleteItem->setEnabled(true);
        displayImage(current);//显示图片·
        break;
    }
}


void MainWindow::on_actionDeleteItem_triggered()
{
    QTreeWidgetItem* item = ui->treeFiles->currentItem();//当前节点
    QTreeWidgetItem* parItem=item->parent();//父节点
    parItem->removeChild(item);//移除当前节点
    delete item;
}


void MainWindow::on_actionAddFolder_triggered()
{
    QString dir=QFileDialog::getExistingDirectory();
    if(!dir.isEmpty())
    {
        QTreeWidgetItem *parItem=ui->treeFiles->currentItem();
        addFolderItem(parItem,dir);
    }

}

void MainWindow::addFolderItem(QTreeWidgetItem *parItem,QString dirName)
{
    QIcon icon(":/ico/ico/AddDir.ico");
    QString NodeText=getFinalFolderName(dirName);//获取最后的文件夹名称

    QTreeWidgetItem *item;
    item=new QTreeWidgetItem(MainWindow::itGroupItem);//组节点
    item->setIcon(colItem,icon);
    item->setText(colItem,NodeText);
    item->setText(colItemType,"type=itGroupItem");
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|
                   Qt::ItemIsAutoTristate);
    item->setData(colItem,Qt::UserRole,QVariant(dirName));
    parItem->addChild(item);//在父节点下面添加子节点
}

QString MainWindow::getFinalFolderName(const QString &fullPathName)
{//从一个完整目录名称里，获得最后的文件夹名称
    int cnt=fullPathName.length();
    int i=fullPathName.lastIndexOf("/");
    QString str=fullPathName.right(cnt-i-1);
    return str;
}

void MainWindow::on_actionAddFiles_triggered()
{
    QStringList files=QFileDialog::getOpenFileNames(this,"选择一个或多个文件","","Images(*.jpg)");
    if(files.isEmpty())
    {
        return;
    }
    QTreeWidgetItem *parItem,*item;
    item=ui->treeFiles->currentItem();
    if(item->type()==itImageItem)//当前节点是图片节点
    {
        parItem=item->parent();//当前节点的父节点为添加的父节点
    }
    else
    {
        parItem=item;
    }

    for(int i=0;i<files.size();++i)
    {
        QString aFilename=files.at(i);//得到一个文件名
        addImageItem(parItem,aFilename);//添加一个图片节点
    }
}

void MainWindow::addImageItem(QTreeWidgetItem *parItem,QString aFilename)
{
    QIcon icon(":/ico/ico/AddFile.ico");
    QString NodeText=getFinalFolderName(aFilename);//获得最后的文件名称
    QTreeWidgetItem *item;
    item = new QTreeWidgetItem(MainWindow::itImageItem);//节点类型
    item->setIcon(colItem,icon);
    item->setText(colItem,NodeText);
    item->setText(colItemType,"type=itImageItem");
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsAutoTristate);
    item->setCheckState(colItem,Qt::Checked);
    item->setData(colItem,Qt::UserRole,QVariant(aFilename));//完整文件名称
    parItem->addChild(item);//在父节点下面添加子节点
}


void MainWindow::on_actionScanItems_triggered()
{
    for(int i=0;i<ui->treeFiles->topLevelItemCount();i++)
    {
        QTreeWidgetItem *item=ui->treeFiles->topLevelItem(i);
        changeItemCaption(item);
    }
}

void MainWindow::changeItemCaption(QTreeWidgetItem *item)
{
    QString str="*" +item->text(colItem);//节点标题前加"*"
    item->setText(colItem,str);
    if(item->childCount()>0)
    {
        for(int i=0;i<item->childCount();i++)
        {
            changeItemCaption(item->child(i));
        }
    }
}

void MainWindow::displayImage(QTreeWidgetItem *item)
{
    QString filename=item->data(colItem,Qt::UserRole).toString();
    LabFileName->setText(filename);
    curPixmap.load(filename);
    on_actionZoomFitH_triggered();//自动适应高度显示
}

void MainWindow::on_actionZoomFitH_triggered()//适应高度显示图片
{
    int H=ui->scrollArea->height();
    int realH=curPixmap.height();
    pixRatio=float(H)/realH;//当前显示比例，需转换为浮点数
    QPixmap pix=curPixmap.scaledToHeight(H-30);//图片缩放到指定高度
    ui->label->setPixmap(pix);
}


void MainWindow::on_actionZoomIn_triggered()
{//放大显示
    pixRatio=pixRatio*1.2;
    int w=pixRatio*curPixmap.width();
    int h=pixRatio*curPixmap.height();
    QPixmap pix=curPixmap.scaled(w,h);
    ui->label->setPixmap(pix);
}


void MainWindow::on_actionZoomRealSize_triggered()
{//实际大小显示
//    pixRatio=1;
    ui->label->setPixmap(curPixmap);
}

void MainWindow::on_actionDockVisible_toggled(bool arg1)
{
    ui->dockWidget_3->setVisible(arg1);
}


void MainWindow::on_actionDockFloat_triggered(bool checked)
{
    ui->dockWidget_3->setFloating(checked);
}


void MainWindow::on_dockWidget_3_visibilityChanged(bool visible)
{
    ui->actionDockVisible->setChecked(visible);
}


void MainWindow::on_dockWidget_3_topLevelChanged(bool topLevel)
{
    ui->actionDockFloat->setChecked(topLevel);
}




void MainWindow::on_actionExit_triggered()
{
    exit(0);
}

