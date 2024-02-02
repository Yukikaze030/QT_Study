#include <QDate>
#include <QDebug>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->splitter);

    labCellIndex = new QLabel("当前单元格坐标:",this);
    labCellIndex->setMinimumWidth(250);
    labCellType = new QLabel("当前单元格类型:",this);
    labCellType->setMinimumWidth(200);
    labStudID=new QLabel("学生 ID:",this);
    labStudID->setMinimumWidth(200);

    ui->statusBar->addWidget(labCellIndex);//加到状态栏
    ui->statusBar->addWidget(labCellType);
    ui->statusBar->addWidget(labStudID);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnSetHeader_clicked()
{
    //设置表头
    QTableWidgetItem *headerItem;
    QStringList headerText;
    headerText<<"姓 名"<<"性 别"<<"出生日期"<<"民 族"<<"分 数"<<"是否党员";

    ui->tableInfo->setColumnCount(headerText.count());
    //通过QStringList初始化表头
    //ui->tableInfo->setHorizontalHeaderLabels(headerText);

    //单独设置表头格式

    for(int i=0;i<ui->tableInfo->columnCount();i++)
    {
        headerItem=new QTableWidgetItem(headerText.at(i));
        QFont font=headerItem->font();
        font.setBold(true);//设置为粗体
        font.setPointSize(12);//字体大小
        headerItem->setForeground(Qt::red);//setTextColor是过时的方法
        headerItem->setFont(font);//设置字体
        ui->tableInfo->setHorizontalHeaderItem(i,headerItem);
    }
    ui->chkBoxHeaderH->setChecked(ui->tableInfo->horizontalHeader()->isVisible());
    qDebug()<<ui->tableInfo->horizontalHeader()->isVisible();
}


void MainWindow::on_btnIniData_clicked()
{
    QString strName,strSex;
    bool isParty=false;
    QDate birth;
    birth.setDate(1980,4,7);//初始化一个日期
    ui->tableInfo->clearContents();//只清除工作区,不清除表头
    int Rows=ui->tableInfo->rowCount();//数据区行数
    for(int i=0;i<Rows;i++)
    {
        strName=QString::asprintf("学生%d",i);
        (i%2)==0?strSex="男":strSex="女";
        CreateItemsARow(i,strName,strSex,birth,"汉族",isParty,70);
        birth = birth.addDays(20);
        isParty=!isParty;
    }
}

void MainWindow::CreateItemsARow(int rowNo,QString Name,QString Sex,QDate birth,QString Nation,bool isPM,int score)
{
    //为每一行单元格创建Item
    QTableWidgetItem *item;
    QString str;
    uint StudID=201605000;//学号基数
    //姓名
    item = new QTableWidgetItem(Name,MainWindow::ctName);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    StudID +=rowNo;//学号=学号基数+行数
    item->setData(Qt::UserRole,QVariant(StudID));//设置studID为data
    ui->tableInfo->setItem(rowNo,MainWindow::colName,item);

    //性别
    QIcon icon;
    Sex=="男"?icon.addFile(":/ico/ico/man.ico"):icon.addFile(":/ico/ico/woman.ico");
    item=new QTableWidgetItem(Sex,MainWindow::ctSex);
    item->setIcon(icon);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableInfo->setItem(rowNo,MainWindow::colSex,item);

    //出生日期
    str=birth.toString("yyyy-MM-dd");//日期转化为字符串
    item=new QTableWidgetItem(str,MainWindow::ctBirth);
    item->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->tableInfo->setItem(rowNo,MainWindow::colBirth,item);

    //民族
    item=new QTableWidgetItem(Nation,MainWindow::ctNation);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableInfo->setItem(rowNo,MainWindow::colNation,item);



    //分数
    str.setNum(score);
    item = new QTableWidgetItem(str,MainWindow::ctScore);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableInfo->setItem(rowNo,MainWindow::colScore,item);

    //是否党员
    item=new QTableWidgetItem("党员",MainWindow::ctPartyM);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    isPM?item->setCheckState(Qt::Checked):item->setCheckState(Qt::Unchecked);
    item->setBackground(Qt::yellow);
    ui->tableInfo->setItem(rowNo,MainWindow::colPartyM,item);

}


void MainWindow::on_tableInfo_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    //当前选择单元格发生变化时响应
    QTableWidgetItem* item = ui->tableInfo->item(currentRow,currentColumn);
    if(item==NULL)
    {
        return;
    }

    labCellIndex->setText(QString::asprintf(("当前单元格坐标: %d行 %d列"),currentRow,currentColumn));
    int cellType=item->type();
    labCellType->setText(QString::asprintf(("当前单元格类型: %d"),cellType));
    item=ui->tableInfo->item(currentRow,MainWindow::colName);
    int ID = item->data(Qt::UserRole).toInt();//读取用户自定义数据
    labStudID->setText(QString::asprintf(("学生ID:%d"),ID));

}


void MainWindow::on_btnInsertRow_clicked()
{
    //插入一行
    int curRow=ui->tableInfo->currentRow();
    ui->tableInfo->insertRow(curRow);//插入一行，不会自动为单元格创建item
    CreateItemsARow(curRow,"新同学","男",QDate::fromString("1990-1-1","yyyy-M-d"),"苗族",true);
}


void MainWindow::on_btnAppendRow_clicked()
{
    //添加一行
    int curRow=ui->tableInfo->rowCount();
    ui->tableInfo->insertRow(curRow);//在表格尾部添加一行
    CreateItemsARow(curRow,"新同学","女",QDate::fromString("1990-1-1","yyyy-M-d"),"苗族",true);
}


void MainWindow::on_btnDelCurRow_clicked()
{
    int curRow=ui->tableInfo->currentRow();
    ui->tableInfo->removeRow(curRow);//删除当前行及其items
}


void MainWindow::on_chkBoxTabEditable_clicked(bool checked)
{
    //设置编辑模式
    if(checked)
        ui->tableInfo->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::SelectedClicked);//双击或获取焦点后单击,进入编辑状态
    else
        ui->tableInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
}




void MainWindow::on_chkBoxHeaderH_clicked(bool checked)
{
    //是否显示行表头
    ui->tableInfo->horizontalHeader()->setVisible(checked);
}



void MainWindow::on_chkBoxHeaderV_clicked(bool checked)
{
    //是否显示列表头
    ui->tableInfo->verticalHeader()->setVisible(checked);
}


void MainWindow::on_chkBoxRowColor_clicked(bool checked)
{
    //间隔行底色
    ui->tableInfo->setAlternatingRowColors(checked);
}




void MainWindow::on_rBtnSelectItem_clicked()
{
    //选择行为:单元格选择
    ui->tableInfo->setSelectionBehavior(QAbstractItemView::SelectItems);
}


void MainWindow::on_rBtnSelectRow_clicked(bool checked)
{
    //选择行为:行选择
    ui->tableInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
}


void MainWindow::on_btnReadToEdit_clicked()
{
    //将所有单元格的内容提取字符串，显示在PlainTextEdit组件里
    QString str;
    QTableWidgetItem *cellItem;
    ui->plainTextEdit->clear();
    for(int i=0;i<ui->tableInfo->rowCount();i++)
    {
        str=QString::asprintf("第 %d 行: ",i+1);
        for(int j=0;j<ui->tableInfo->columnCount()-1;j++)
        {
            cellItem=ui->tableInfo->item(i,j);//获取单元格的item
            str=str+cellItem->text()+"  ";//字符串连接
        }
        cellItem=ui->tableInfo->item(i,colPartyM);
        if(cellItem->checkState()==Qt::Checked)
        {
            str+="党员";
        }
        else
        {
            str+="群众";
        }
        ui->plainTextEdit->appendPlainText(str);
    }
}

