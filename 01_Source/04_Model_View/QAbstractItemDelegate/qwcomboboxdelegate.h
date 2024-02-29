#ifndef QWCOMBOBOXDELEGATE_H
#define QWCOMBOBOXDELEGATE_H
#pragma execution_character_set("utf-8")
#include <QStyledItemDelegate>
#include <QComboBox>
class QWComboBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit QWComboBoxDelegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent,const QStyleOptionViewItem &option,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const Q_DECL_OVERRIDE;
    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option,const QModelIndex &index) const Q_DECL_OVERRIDE;
};

#endif // QWCOMBOBOXDELEGATE_H


