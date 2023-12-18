#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->m_horizontalSlider_Alpha,SIGNAL(valueChanged(int)),this,SLOT(on_m_horizontalSlider_Red_valueChanged(int)));
    connect(ui->m_horizontalSlider_Green,SIGNAL(valueChanged(int)),this,SLOT(on_m_horizontalSlider_Red_valueChanged(int)));
    connect(ui->m_horizontalSlider_Blue,SIGNAL(valueChanged(int)),this,SLOT(on_m_horizontalSlider_Red_valueChanged(int)));

    InitUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitUI()
{

}

void MainWindow::on_m_horizontalSlider_Red_valueChanged(int value)
{
    Q_UNUSED(value);

    QColor color;
    int R = ui->m_horizontalSlider_Red->value();
    int G = ui->m_horizontalSlider_Green->value();
    int B = ui->m_horizontalSlider_Blue->value();
    int Alpha = ui->m_horizontalSlider_Alpha->value();
    color.setRgb(R,G,B,Alpha);
    QPalette pal = ui->m_textEdit_Coloer->palette();
    pal.setColor(QPalette::Base,color);
    ui->m_textEdit_Coloer->setPalette(pal);
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->horizontalScrollBar->setValue(value);
    ui->progressBar->setValue(value);

}


void MainWindow::on_dial_valueChanged(int value)
{
    ui->lcdNumber->display(value);
}

