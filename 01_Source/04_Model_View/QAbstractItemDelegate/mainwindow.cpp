#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->splitter);
    theModel = new QStandardItemModel(2,FixedColumnCount,this);
    theSelection = new QItemSelectionModel(theModel);

    connect(theSelection,
            static_cast<void (QItemSelectionModel::*)(const QModelIndex &current, const QModelIndex &previous)>(&QItemSelectionModel::currentChanged),
            this,
            &MainWindow::on_currentChanged);

    ui->tableView->setModel(theModel);
    ui->tableView->setSelectionModel(theSelection);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);

    ui->tableView->setItemDelegateForColumn(0,&intSpinDelegate);
    ui->tableView->setItemDelegateForColumn(1,&floatSpinDelegate);
    ui->tableView->setItemDelegateForColumn(2,&floatSpinDelegate);
    ui->tableView->setItemDelegateForColumn(3,&floatSpinDelegate);
    ui->tableView->setItemDelegateForColumn(4,&comboBoxDelegate);

    //添加状态栏
    LabCurFile = new QLabel(this);
    LabCellPos = new QLabel(this);
    LabCellText = new QLabel(this);

//    LabCurFile->setText("File");
//    LabCellPos->setText("Pos");
//    LabCellText->setText("Text");

    ui->statusBar->addWidget(LabCurFile);
    ui->statusBar->addWidget(LabCellPos);
    ui->statusBar->addWidget(LabCellText);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_currentChanged(const QModelIndex &current,const QModelIndex &previous)
{
    if(current.isValid())
    {
        LabCellPos->setText(QString::asprintf("当前单元格:%d行,%d列",current.row(),current.column()));
        QStandardItem* aItem=theModel->itemFromIndex(current);
        this->LabCellText->setText("单元格内容："+aItem->text());
        QFont font=aItem->font();
        ui->actionFontBold->setChecked(font.bold());
    }
}



void MainWindow::on_actionOpen_triggered()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString aFileName = QFileDialog::getOpenFileName(this,"打开一个文件",curPath,"数据文件(*.txt);;所有文件(*.*)");
    if(aFileName.isEmpty())
    {
        return;
    }

    QStringList fFileContent;
    QFile aFile(aFileName);
    if(aFile.open(QIODevice::ReadOnly | QIODevice::Text))//打开文件
    {
        QTextStream aStream(&aFile);//用文件流读取文件
        ui->PlaninTextEdit->clear();
        while(!aStream.atEnd())
        {
            QString str=aStream.readLine();//逐行读取
            ui->PlaninTextEdit->appendPlainText(str);
            fFileContent.append(str);
        }
        aFile.close();
        this->LabCurFile->setText("当前文件："+aFileName);
        iniModelFromStringList(fFileContent);
    }
}

void MainWindow::iniModelFromStringList(QStringList& aFileContent)
{
    //从StringList中获取数据，初始化数据模型
    int rowCnt=aFileContent.count();//文件总行数，第一行为标题。
    theModel->setRowCount(rowCnt-1);

    //设置表头
    QString header=aFileContent.at(0);
    QStringList headerList=header.split(QRegExp("\\s+"),QString::SkipEmptyParts);
    theModel->setHorizontalHeaderLabels(headerList);//设置表头文字

    //设置表格数据d
    QStandardItem   *aItem;
    QStringList tmpList;
    int j;
    for(int i = 1;i<rowCnt;i++)
    {
        QString aLineText=aFileContent.at(i);
        tmpList=aLineText.split(QRegExp("\\s+"),QString::SkipEmptyParts);
        for(j=0;j<FixedColumnCount-1;j++)
        {
            aItem=new QStandardItem(tmpList.at(j));
            theModel->setItem(i-1,j,aItem);
        }

        //Check
        aItem=new QStandardItem(headerList.at(j));
        aItem->setCheckable(true);
        if(tmpList.at(j)=="0")
        {
            aItem->setCheckState(Qt::Unchecked);
        }
        else
        {
            aItem->setCheckState(Qt::Checked);
        }
        theModel->setItem(i-1,j,aItem);
    }
}



void MainWindow::on_actionAppend_triggered()
{
    QList<QStandardItem*> aItemList;//列表类
    QStandardItem  *aItem;
    for(int i=0;i<FixedColumnCount-1;i++)
    {
        aItem=new QStandardItem("0");
        aItemList << aItem;
    }

    //获取最后一列的表头文字
    QString str=theModel->headerData(theModel->columnCount()-1,Qt::Horizontal,Qt::DisplayRole).toString();
    aItem=new QStandardItem(str);
    aItem->setCheckable(true);
    aItemList << aItem;

    theModel->insertRow(theModel->rowCount(),aItemList);
    QModelIndex curIndex = theModel->index(theModel->rowCount()-1,0);
    theSelection->clearSelection();
    theSelection->setCurrentIndex(curIndex,QItemSelectionModel::Select);

}


void MainWindow::on_actionInsert_triggered()
{
    QList<QStandardItem*> aItemList;//列表类
    QStandardItem  *aItem;
    for(int i=0;i<FixedColumnCount-1;i++)
    {
        aItem=new QStandardItem("0");
        aItemList << aItem;
    }


    QString str=theModel->headerData(theModel->columnCount()-1,Qt::Horizontal,Qt::DisplayRole).toString();
    aItem=new QStandardItem(str);
    aItem->setCheckable(true);
    aItemList << aItem;

    QModelIndex curIndex = theSelection->currentIndex();
    theModel->insertRow(curIndex.row(),aItemList);
    theSelection->clearSelection();
    theSelection->setCurrentIndex(curIndex,QItemSelectionModel::Select);

}


void MainWindow::on_actionDelete_triggered()
{
    QModelIndex curIndex=theSelection->currentIndex();
    if(curIndex.row () == theModel->rowCount()-1)
    {
        theModel->removeRow(curIndex.row());
    }else
    {
        theModel->removeRow(curIndex.row());
        theSelection->setCurrentIndex(curIndex,QItemSelectionModel::Select);
    }
}


void MainWindow::on_actionAlignLeft_triggered()
{
    if(!theSelection->hasSelection())
    {
        return;
    }
    QModelIndexList selectedIndex = theSelection->selectedIndexes();
    for (int var = 0; var < selectedIndex.count(); ++var) {
        QModelIndex aIndex=selectedIndex.at(var);
        QStandardItem* aItem=theModel->itemFromIndex(aIndex);
        aItem->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    }
}


void MainWindow::on_actionAlignCenter_triggered()
{
    if(!theSelection->hasSelection())
    {
        return;
    }
    QModelIndexList selectedIndex = theSelection->selectedIndexes();
    for (int var = 0; var < selectedIndex.count(); ++var) {
        QModelIndex aIndex=selectedIndex.at(var);
        QStandardItem* aItem=theModel->itemFromIndex(aIndex);
        aItem->setTextAlignment(Qt::AlignCenter|Qt::AlignVCenter);
    }
}


void MainWindow::on_actionAlignRight_triggered()
{
    if(!theSelection->hasSelection())
    {
        return;
    }
    QModelIndexList selectedIndex = theSelection->selectedIndexes();
    for (int var = 0; var < selectedIndex.count(); ++var) {
        QModelIndex aIndex=selectedIndex.at(var);
        QStandardItem* aItem=theModel->itemFromIndex(aIndex);
        aItem->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
}


void MainWindow::on_actionFontBold_triggered()
{
    if(!theSelection->hasSelection())
    {
        return;
    }
    QModelIndexList selectedIndex = theSelection->selectedIndexes();
    for (int var = 0; var < selectedIndex.count(); ++var) {
        QModelIndex aIndex=selectedIndex.at(var);
        QStandardItem* aItem=theModel->itemFromIndex(aIndex);
        QFont font = aItem->font();
        bool checked = !font.bold();
        font.setBold(checked);
        aItem->setFont(font);
    }
}


void MainWindow::on_actionSave_triggered()
{
    QString curPath=QCoreApplication::applicationDirPath();
    QString aFileName=QFileDialog::getSaveFileName(this,"选择一个文件",curPath,"数据文件(*.txt);;所有文件(*.*)");
    if(aFileName.isEmpty())
    {
        return;
    }
    QFile aFile(aFileName);
    if(!(aFile.open(QIODevice::ReadWrite | QIODevice::Text |QIODevice::Truncate)))
        return;

    QTextStream aStream(&aFile);
    QStandardItem *aItem;
    int i,j;
    QString str;
    ui->PlaninTextEdit->clear();

    for(i=0;i<theModel->columnCount();i++)
    {
        aItem=theModel->horizontalHeaderItem(i);
        str=str+aItem->text()+"\t\t";
    }

    ui->PlaninTextEdit->appendPlainText(str);
    for(i=0;i<theModel->rowCount()-1;i++)
    {
        str="";
        for(j=0;j<theModel->columnCount()-1;j++)
        {
            aItem=theModel->item(i,j);
            str=str+aItem->text()+QString::asprintf("\t\t");
        }

        aItem=theModel->item(i,j);
        if(aItem->checkState() == Qt::Checked)
        {
            str=str+"1";
        }
        else
        {
            str=str+"0";
        }
        ui->PlaninTextEdit->appendPlainText(str);
        aStream<<str<<"\n";
    }
}


void MainWindow::on_actionModelData_triggered()
{

    QStandardItem *aItem;
    int i,j;
    QString str;
    ui->PlaninTextEdit->clear();

    for(i=0;i<theModel->columnCount();i++)
    {
        aItem=theModel->horizontalHeaderItem(i);
        str=str+aItem->text()+"\t\t";
    }

    ui->PlaninTextEdit->appendPlainText(str);
    for(i=0;i<theModel->rowCount()-1;i++)
    {
        str="";
        for(j=0;j<theModel->columnCount()-1;j++)
        {
            aItem=theModel->item(i,j);
            str=str+aItem->text()+QString::asprintf("\t\t");
        }

        aItem=theModel->item(i,j);
        if(aItem->checkState() == Qt::Checked)
        {
            str=str+"1";
        }
        else
        {
            str=str+"0";
        }
        ui->PlaninTextEdit->appendPlainText(str);
        //aStream<<str<<"\n";
    }
}

