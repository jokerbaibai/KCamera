#ifndef DEVICEDELEGATE_H
#define DEVICEDELEGATE_H

#include <QStyledItemDelegate>
#include <QPushButton>

class DeviceDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    DeviceDelegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

signals:
    void connectClicked(const QModelIndex &index) ;

private slots:
    void handleButtonClick();

};

#endif // DEVICEDELEGATE_H
