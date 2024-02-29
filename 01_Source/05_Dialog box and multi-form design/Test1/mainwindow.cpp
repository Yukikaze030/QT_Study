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

void MainWindow::on_btnOpen_clicked()
{
    QString curPath=QDir::currentPath();//起始目录
    QString dlgTitle="选择一个文件";
    QString filter="文本文件(*.txt);;图片文件(*.jpg *.gif);;所有文件(*.*)";


    QString aFileName=QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);
    if(!aFileName.isEmpty())
    {
       ui->PlainTextEdit->appendPlainText(aFileName);
    }
}


void MainWindow::on_btnOpenMulti_clicked()
{
    QString curPath=QDir::currentPath();//起始目录
    QString dlgTitle="选择一个文件";
    QString filter="文本文件(*.txt);;图片文件(*.jpg *.gif);;所有文件(*.*)";


    QStringList aFileList=QFileDialog::getOpenFileNames(this,dlgTitle,curPath,filter);
    if(!aFileList.isEmpty())
    {
        for(auto aFileName : aFileList)
        {
            ui->PlainTextEdit->appendPlainText(aFileName);
        }
    }
}


void MainWindow::on_btnSelDir_clicked()
{
    QString curPath=QCoreApplication::applicationDirPath();//起始目录
    QString dlgTitle="选择一个目录";
//    QString filter="文本文件(*.txt);;图片文件(*.jpg *.gif);;所有文件(*.*)";


    QString selectedDir=QFileDialog::getExistingDirectory(this,dlgTitle,curPath,QFileDialog::ShowDirsOnly);
    if(!selectedDir.isEmpty())
    {
       ui->PlainTextEdit->appendPlainText(selectedDir);
    }
}


void MainWindow::on_btnSave_clicked()
{
    QString curPath=QCoreApplication::applicationDirPath();//起始目录
    QString dlgTitle="保存文件";
    QString filter="h文件(*.h);;C++文件(*.cpp);;所有文件(*.*)";


    QString aFileName=QFileDialog::getSaveFileName(this,dlgTitle,curPath,filter);
    if(!aFileName.isEmpty())
    {
       ui->PlainTextEdit->appendPlainText(aFileName);
    }
}


void MainWindow::on_btnColor_clicked()
{
    QPalette pal=ui->PlainTextEdit->palette();//获取现有palette
    QColor iniColor=pal.color(QPalette::Text);//现有的文字颜色
    QColor color=QColorDialog::getColor(iniColor,this,"选择颜色");
    if(color.isValid())
    {
        pal.setColor(QPalette::Text,color);
        ui->PlainTextEdit->setPalette(pal);
    }
}


void MainWindow::on_btnFont_clicked()
{
    QFont iniFont = ui->PlainTextEdit->font();
    bool ok=false;
    QFont font=QFontDialog::getFont(&ok,iniFont);
    if(&ok)
    {
        ui->PlainTextEdit->setFont(font);
    }
}


void MainWindow::on_btnInputString_clicked()
{
    QString dlgTitle="输入文字对话框";
    QString txtLabel="请输入文件名";
    QString defaultInput="新建文件.txt";

    QLineEdit::EchoMode echoMode = QLineEdit::Normal;//
    //QLineEdit::EchoMode echoMode = QLineEdit::Password; //QLineEdit::Password //密码输入
    bool ok=false;
    QString text=QInputDialog::getText(this,dlgTitle,txtLabel,echoMode,defaultInput,&ok);

    if(ok && !text.isEmpty())
    {
        ui->PlainTextEdit->appendPlainText(text);
    }
}


void MainWindow::on_btnInputInt_clicked()
{
    QString dlgTitle="输入整数对话框";
    QString txtLabel="设置字体大小";
    int defaultValue=ui->PlainTextEdit->font().pointSize();
    int minValue=6,maxValue=50,stepValue=1;


    bool ok=false;
    int inputValue=QInputDialog::getInt(this,dlgTitle,txtLabel,defaultValue,minValue,maxValue,stepValue,&ok);

    if(ok)
    {
        QFont font=ui->PlainTextEdit->font();
        font.setPointSize(inputValue);
        ui->PlainTextEdit->setFont(font);
    }
}


void MainWindow::on_btnInputFloat_clicked()
{
    QString dlgTitle="输入浮点数对话框";
    QString txtLabel="输入一个浮点数";
    float defaultValue=3.13;
    float minValue=0,maxValue=10000;
    int decimals=2;
    //int minValue=6,maxValue=50,stepValue=1;


    bool ok=false;
    float inputValue=QInputDialog::getDouble(this,dlgTitle,txtLabel,defaultValue,minValue,maxValue,decimals,&ok);

    if(ok)
    {
        QString str=QString::asprintf("输入了一个浮点数:%.2f",inputValue);
        ui->PlainTextEdit->appendPlainText(str);
    }
}


void MainWindow::on_btnInputItem_clicked()
{
    QStringList items;
    items<<"优秀"<<"良好"<<"合格"<<"不合格";
    QString dlgTitle="条目选择对话框";
    QString txtLabel="请选择级别";
    int curIndex=0;//初始选择项
    bool editable=true;//ComboBox是否可编辑
    bool ok=false;
    QString text=QInputDialog::getItem(this,dlgTitle, txtLabel,items,curIndex,editable,&ok);

    if(ok&&!text.isEmpty())
    {
        ui->PlainTextEdit->appendPlainText(text);
    }
}


void MainWindow::on_btnMsgInformation_clicked()
{
    QString dlgTitle="information 消息框";
    QString strInfo="文件已经打开，字体大小已设置";
    //QMess
}

