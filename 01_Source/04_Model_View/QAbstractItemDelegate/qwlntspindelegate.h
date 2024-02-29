#ifndef QWLNTSPINDELEGATE_H
#define QWLNTSPINDELEGATE_H

#include <QStyledItemDelegate>
#include <QSpinBox>
class QWlntSpinDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    QWlntSpinDelegate(QObject *parent=0);

    QWidget *createEditor(QWidget *parent,const QStyleOptionViewItem &option,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const Q_DECL_OVERRIDE;
    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option,const QModelIndex &index) const Q_DECL_OVERRIDE;
};

#endif // QWLNTSPINDELEGATE_H
