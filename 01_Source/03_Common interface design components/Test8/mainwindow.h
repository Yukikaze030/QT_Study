#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
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
    void on_btnSetHeader_clicked();

    void on_btnIniData_clicked();

    void on_tableInfo_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_btnInsertRow_clicked();

    void on_btnAppendRow_clicked();

    void on_btnDelCurRow_clicked();

    void on_chkBoxTabEditable_clicked(bool checked);

    void on_chkBoxHeaderH_clicked(bool checked);

    void on_chkBoxHeaderV_clicked(bool checked);

    void on_chkBoxRowColor_clicked(bool checked);

    void on_rBtnSelectItem_clicked();

    void on_rBtnSelectRow_clicked(bool checked);

    void on_btnReadToEdit_clicked();

private:
    Ui::MainWindow *ui;

private:
    //自定义单元格Type，在创建item的时候使用
    enum CellType{ctName=1000,ctSex,ctBirth,ctNation,ctScore,ctPartyM};
    //各字段在表格中的列号
    enum FieldColNum{colName=0,colSex,colBirth,colNation,colScore,colPartyM};

    QLabel *labCellIndex;//状态栏上用于显示单元格的行号、列号
    QLabel *labCellType;//状态栏上用于显示单元格的Type
    QLabel *labStudID;//状态栏上用于显示学号

    void CreateItemsARow(int rowNo,QString Name,QString Sex,QDate birth,QString Nation,bool isPM,int score=70);//为某一行创建items
};
#endif // MAINWINDOW_H
