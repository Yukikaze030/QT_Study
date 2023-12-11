#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_m_pushButton_Append_clicked();

    void on_m_pushButton_Prepend_clicked();

    void on_m_pushButton_toUpper_clicked();

    void on_m_pushButton_toLower_clicked();

    void on_m_pushButton_left_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
