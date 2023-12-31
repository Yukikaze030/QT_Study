#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createSelectionPopMenu();
//    QMenu* Menu = new QMenu(ui->m_List_toolButton_Selection);
//    Menu->addAction(ui->actionSelectAll);
//    Menu->addAction(ui->actionCheckOutAll);
//    Menu->addAction(ui->actionInvertSelection);
    //ui->actionAddItem->setMenu(Menu);

//    QToolButton* m_button = new QToolButton();
//    m_button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
//    m_button->setDefaultAction(ui->actionItemSelection);
//    m_button->setMenu(Menu);

//    ui->toolBar_2->addWidget(m_button);

    ui->m_toolButton_Reset->setDefaultAction(ui->actionResetList);
    ui->m_toolButton_Clear->setDefaultAction(ui->actionClearList);
    ui->m_toolButton_Delete->setDefaultAction(ui->actionDeleteItem);
    ui->m_toolButton_Insert->setDefaultAction(ui->actionInsertEntry);
    ui->m_toolButton_Add->setDefaultAction(ui->actionAddItem);

    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
//    ui->m_List_toolButton_Selection->setDefaultAction(ui->actionItemSelection);
//    ui->m_List_toolButton_Selection->setMenu(Menu);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionItemSelection_triggered()
{

}


void MainWindow::on_actionResetList_triggered()
{
    QListWidgetItem *aItem;
    QIcon aIcon;
    aIcon.addFile(":/ico/normal.ico");

    bool chk=ui->m_checkBox_ListEditable->isChecked();
    ui->listWidget->clear();
    for(int i = 0;i<10;i++)
    {
        QString str=QString::asprintf("Item %d",i);
        aItem = new QListWidgetItem();
        aItem->setText(str);
        aItem->setIcon(aIcon);
        aItem->setCheckState(Qt::Checked);
        if(chk)
        {
            aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        }
        else
        {
            aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        }
        ui->listWidget->addItem(aItem);
    }

}


void MainWindow::on_actionInsertEntry_triggered()
{
    QIcon aIcon;
    aIcon.addFile(":/ico/normal.ico");
    bool chk=ui->m_checkBox_ListEditable->isChecked();
    QListWidgetItem *aItem=new QListWidgetItem("New Inserted Item");
    aItem->setIcon(aIcon);
    aItem->setCheckState(Qt::Checked);
    if(chk)
    {
        aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
    }
    else
    {
        aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
    }
    int row = ui->listWidget->currentRow();
    ui->listWidget->insertItem(row,aItem);

}


void MainWindow::on_actionDeleteItem_triggered()
{
    int row = ui->listWidget->currentRow();
    QListWidgetItem* aItem=ui->listWidget->takeItem(row);
    delete aItem;
}


void MainWindow::on_actionClearList_triggered()
{
    ui->listWidget->clear();
}


void MainWindow::on_actionSelectAll_triggered()
{
    int cnt=ui->listWidget->count();
    for(int i = 0 ; i < cnt;i++)
    {
        QListWidgetItem* aItem = ui->listWidget->item(i);
        aItem->setCheckState(Qt::Checked);
    }
}




void MainWindow::on_actionCheckOutAll_triggered()
{
    int cnt=ui->listWidget->count();
    for(int i = 0 ; i < cnt;i++)
    {
        QListWidgetItem* aItem = ui->listWidget->item(i);
        aItem->setCheckState(Qt::Unchecked);
    }
}


void MainWindow::on_actionInvertSelection_triggered()
{
    int cnt=ui->listWidget->count();
    for(int i = 0 ; i < cnt;i++)
    {
        QListWidgetItem* aItem = ui->listWidget->item(i);

        switch(aItem->checkState())
        {
        case Qt::PartiallyChecked:
        case Qt::Checked:
            aItem->setCheckState(Qt::Unchecked);
            break;
        case Qt::Unchecked:
            aItem->setCheckState(Qt::Checked);
            break;
        }
    }
}


void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    QString str;
    if(current != NULL)
    {
        if(previous==NULL)
        {
            str="当前项:" +current->text();
        }
        else
        {
            str="前一项:" +previous->text()+"; 当前项:"+current->text();
        }
        ui->lineEdit->setText(str);

    }
}

void MainWindow::createSelectionPopMenu()
{
    //创建下拉菜单
    QMenu* menuSelection = new QMenu(this);
    menuSelection->addAction(ui->actionSelectAll);
    menuSelection->addAction(ui->actionCheckOutAll);
    menuSelection->addAction(ui->actionInvertSelection);

    //ListWidget上方的m_List_toolButton_InvertSelection按钮
    ui->m_List_toolButton_Selection->setPopupMode(QToolButton::MenuButtonPopup);
    ui->m_List_toolButton_Selection->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->m_List_toolButton_Selection->setDefaultAction(ui->actionItemSelection);
    ui->m_List_toolButton_Selection->setMenu(menuSelection);

    //工具栏上的下拉式菜单按钮
    QToolButton *aBtn=new QToolButton(this);
    aBtn->setPopupMode(QToolButton::InstantPopup);
    aBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    aBtn->setDefaultAction(ui->actionItemSelection);
    aBtn->setMenu(menuSelection);

    ui->toolBar_2->addWidget(aBtn);
    ui->toolBar_2->addSeparator();
    ui->toolBar_2->addAction(ui->actionExit);

}



void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    QMenu* menuList=new QMenu(this);

    menuList->addAction(ui->actionResetList);
    menuList->addAction(ui->actionClearList);
    menuList->addAction(ui->actionInsertEntry);
    menuList->addAction(ui->actionAddItem);
    menuList->addAction(ui->actionDeleteItem);
    menuList->addSeparator();
    menuList->addAction(ui->actionSelectAll);
    menuList->addAction(ui->actionCheckOutAll);
    menuList->addAction(ui->actionInvertSelection);
    menuList->exec(QCursor::pos());
    delete menuList;
}

