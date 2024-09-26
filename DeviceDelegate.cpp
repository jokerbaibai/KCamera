#include "DeviceDelegate.h"
#include <QHBoxLayout>
#include <QPushButton>

DeviceDelegate::DeviceDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

QWidget *DeviceDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (index.parent().isValid()) {  // 确保这是第二级（设备信息）
        QWidget *editor = new QWidget(parent);
        QHBoxLayout *layout = new QHBoxLayout(editor);
        layout->setContentsMargins(0, 0, 0, 0);

        QPushButton *button = new QPushButton("Connect", editor);
        layout->addWidget(button);

        connect(button, &QPushButton::clicked, this, &DeviceDelegate::handleButtonClick);

        return editor;
    } else {
        return nullptr;  // 如果是第一级（接口信息），不添加按钮
    }
}

void DeviceDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    // 可以在这里设置按钮的初始状态
}

void DeviceDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    // 可以在这里处理编辑后的数据
}

void DeviceDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (editor) {
        editor->setGeometry(option.rect);
    }
}

void DeviceDelegate::handleButtonClick() {
    QWidget *senderWidget = qobject_cast<QWidget*>(sender()->parent());
    QModelIndex index = senderWidget->property("index").value<QModelIndex>();
    emit connectClicked(index);
}
