#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma execution_character_set("utf-8")

#include <QMainWindow>
#include <QLabel>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QCoreApplication>
#include <QFileDialog>
#include <QTextStream>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define FixedColumnCount 6
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionAppend_triggered();

    void on_actionInsert_triggered();

    void on_actionDelete_triggered();

    void on_actionAlignLeft_triggered();

    void on_actionAlignCenter_triggered();

    void on_actionAlignRight_triggered();

    void on_actionFontBold_triggered();

    void on_actionSave_triggered();

    void on_actionModelData_triggered();

private:
    Ui::MainWindow *ui;
    QLabel *LabCurFile;//当前文件
    QLabel *LabCellPos;//当前单元格行列号
    QLabel *LabCellText;//当前单元格内容

    QStandardItemModel *theModel;//数据模型
    QItemSelectionModel *theSelection;//选择模型

    void iniModelFromStringList(QStringList&);
private:
    void on_currentChanged(const QModelIndex &current,const QModelIndex &previous);

};
#endif // MAINWINDOW_H
