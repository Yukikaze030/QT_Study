#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_m_pushButton_ResetList_clicked();

    void on_m_pushButton_ResetCity_clicked();

    void on_m_pushButton_TextAddComboBox_clicked();

    void on_m_checkBox_ReadOnly_stateChanged(int arg1);

    void on_textBrowser_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
