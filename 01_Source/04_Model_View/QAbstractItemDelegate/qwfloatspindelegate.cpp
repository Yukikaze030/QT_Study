#include "qwfloatspindelegate.h"

QWFloatSpinDelegate::QWFloatSpinDelegate(QObject *parent):QStyledItemDelegate(parent)
{

}

//创建需要的编辑组件
QWidget *QWFloatSpinDelegate::createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index) const
{
    QSpinBox *editor = new QSpinBox(parent);
    editor->setFrame(false);
    editor->setMinimum(0);
    editor->setMaximum(10000);
    return editor;
}

//用于数据模型获取数值
void QWFloatSpinDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int value = index.model()->data(index,Qt::EditRole).toInt();
    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    spinBox->setValue(value);
}

//代理编辑器上的值更新给数据模型，完成编辑时自动调用
void QWFloatSpinDelegate ::setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const
{
    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    spinBox->interpretText();
    int value = spinBox->value();
    model->setData(index,value,Qt::EditRole);
}

void QWFloatSpinDelegate::updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option,const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
