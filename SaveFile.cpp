#include "SaveFile.h"

SaveFile::SaveFile() {}
/*
//功能
void MainWindow::save_image(){
    if (monitor && monitor->imageLabel) {
        QPixmap pixmap = monitor->imageLabel->grab(); // 捕获当前显示的图像
        QString filePath = QFileDialog::getSaveFileName(this, "保存图片", "", "PNG Files (*.png);;All Files (*)");
        if (!filePath.isEmpty()) {
            pixmap.save(filePath, "PNG");
            QMessageBox::information(this, "图片保存", "图片已成功保存为 PNG 格式。");
        }
    }
}

void MainWindow::save_video(){
    if (!recording) {
        // 开始录制
        recording = true;
        QMessageBox::information(this, "录制开始", "视频录制已开始。");

        // 更新按钮文本
        recordButton->setText("停止录制");

        // 设置定时器周期性地捕获当前显示的图像
        recordingTimer = new QTimer(this);
        connect(recordingTimer, &QTimer::timeout, this, &MainWindow::captureFrame);
        recordingTimer->start(1000 / 30); // 30 FPS
    } else {
        // 停止录制
        recording = false;
        recordingTimer->stop();
        delete recordingTimer;
        recordingTimer = nullptr;

        // 打开文件保存对话框以获取保存路径
        QString filePath = QFileDialog::getSaveFileName(this, "保存视频", "", "视频文件 (*.mp4);;所有文件 (*)");
        if (!filePath.isEmpty()) {
            // 将缓冲区数据写入文件
            QFile file(filePath);
            if (file.open(QIODevice::WriteOnly)) {
                file.write(buffer->data());
                file.close();
                QMessageBox::information(this, "保存成功", "视频已保存至文件。");
            } else {
                QMessageBox::warning(this, "保存失败", "无法打开文件进行写入。");
            }
        }

        // 清空缓冲区
        buffer->close();
        buffer->open(QIODevice::ReadWrite);

        // 更新按钮文本
        recordButton->setText("开始录制");
    }
}
void MainWindow::captureFrame() {
    if (monitor && monitor->imageLabel) {
        QPixmap pixmap = monitor->imageLabel->grab();  // 捕获当前显示的图像
        QImage image = pixmap.toImage();                // 转换为 QImage

        // 将 QImage 转换为 PNG 格式的数据
        QByteArray byteArray;
        QBuffer buffer1(&byteArray);
        buffer1.open(QIODevice::WriteOnly);
        image.save(&buffer1, "PNG");

        // 将数据追加到内存缓冲区
        buffer->write(byteArray);
    }
}*/
