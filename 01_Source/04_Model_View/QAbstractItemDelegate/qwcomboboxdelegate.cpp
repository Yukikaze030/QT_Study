#include "qwcomboboxdelegate.h"

QWComboBoxDelegate::QWComboBoxDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{

}

//创建需要的编辑组件
QWidget *QWComboBoxDelegate::createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);
    QStringList str;
    str<<"极差"<<"差"<<"合格"<<"优秀";
    editor->setFrame(false);
    editor->addItems(str);
    return editor;
}

//用于数据模型获取数值
void QWComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int value = index.model()->data(index,Qt::EditRole).toInt();
    QComboBox *ComboBox = static_cast<QComboBox*>(editor);
    ComboBox->setCurrentIndex(value);
}

//代理编辑器上的值更新给数据模型，完成编辑时自动调用
void QWComboBoxDelegate ::setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const
{
    QComboBox *ComboBox = static_cast<QComboBox*>(editor);
    //ComboBox->interpretText();
    QString value = ComboBox->currentText();
    model->setData(index,value,Qt::EditRole);
}

void QWComboBoxDelegate::updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option,const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
