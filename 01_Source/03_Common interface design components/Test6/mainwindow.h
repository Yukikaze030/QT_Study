#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
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

    void on_actionItemSelection_triggered();

    void on_actionResetList_triggered();

    void on_actionInsertEntry_triggered();

    void on_actionDeleteItem_triggered();

    void on_actionClearList_triggered();

    void on_actionSelectAll_triggered();

    void on_actionCheckOutAll_triggered();

    void on_actionInvertSelection_triggered();

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_listWidget_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;
    void createSelectionPopMenu();
};
#endif // MAINWINDOW_H
