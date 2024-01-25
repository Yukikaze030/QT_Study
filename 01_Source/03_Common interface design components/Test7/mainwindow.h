#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTreeWidgetItem>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_treeFiles_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_actionDeleteItem_triggered();

    void on_actionAddFolder_triggered();

    void on_actionAddFiles_triggered();

    void on_actionScanItems_triggered();

    void on_actionZoomFitH_triggered();

    void on_actionZoomIn_triggered();

    void on_actionZoomRealSize_triggered();


    void on_actionDockFloat_triggered(bool checked);

    void on_dockWidget_3_visibilityChanged(bool visible);

    void on_dockWidget_3_topLevelChanged(bool topLevel);

    void on_actionDockVisible_toggled(bool arg1);

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;

private:
    //枚举类型treeItemType,创建节点时用作type参数，自定义类型必须大于1000
    enum treeItemType{itTopItem=1001,itGroupItem,itImageItem};
    enum treeColNum{colItem=0,colItemType=1};//目录树列的编号

    QLabel *LabFileName;//用于状态栏文件名显示
    QPixmap curPixmap;//当前的图片
    float pixRatio;//图片缩放比例

    void iniTree();//目录树初始化
    void addFolderItem(QTreeWidgetItem *parItem,QString dirName);//添加目录
    QString getFinalFolderName(const QString &fullPaathName);//提取目录名称
    void addImageItem(QTreeWidgetItem *parItem,QString aFilename);//添加图片
    void displayImage(QTreeWidgetItem *item);//显示有关图片节点的图片
    void changeItemCaption(QTreeWidgetItem *item);//遍历改变节点标题



};
#endif // MAINWINDOW_H
