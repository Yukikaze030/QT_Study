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
    void on_m_horizontalSlider_Red_valueChanged(int value);
    void on_horizontalSlider_valueChanged(int value);

    void on_dial_valueChanged(int value);

private:
    void InitUI();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
