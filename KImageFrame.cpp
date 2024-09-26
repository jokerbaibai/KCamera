#include "KImageFrame.h"
#include <iostream>
#include <WinSock2.h>
//构造函数
KImageFrame::KImageFrame(){
    height=1080;
    width=1440;
    channels=3;
    size=1440*1080*3;
    line=0;
    complete=false;
    buffer = static_cast<uint8_t*>(malloc(size));
    memset(buffer, 0, size);
    if (!buffer) {
        std::cerr << "Failed to allocate memory for image buffer" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}
KImageFrame::KImageFrame(int h,int w,int c){
    height=h;
    width=w;
    channels=c;
    size=h*w*c;
    line=0;
    complete=false;
    buffer = static_cast<uint8_t*>(malloc(size));
    memset(buffer, 0, size);
    if (!buffer) {
        std::cerr << "Failed to allocate memory for image buffer" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}
//析构函数
KImageFrame::~KImageFrame() {
    free(buffer);
}

//
bool KImageFrame::addPacket(const uint8_t* packet, int length) {
    // 检查标识符（第14-17字节）
    uint32_t identifier;
    std::memcpy(&identifier, packet + 14, sizeof(identifier));

    if (ntohl(identifier) != 0x11111111) {
        std::cout << "Invalid identifier: " << std::hex << ntohl(identifier) << std::dec << std::endl;
        return false; // 忽略不匹配的包
    }

    const int* header = reinterpret_cast<const int*>(packet);
    int count = ntohl(header[0]);
    int num = ntohl(header[1]);

    if (complete || line + num > 1440) {
        std::cout << "Overflow!" << std::endl;
        return false; // 防止溢出
    }

    std::memcpy(buffer + count * 1080 * 3, packet + 18, num * 1080 * 3);
    line += num;
    //std::cout << "Count: " << count << " Line: " << line << std::endl;

    if (line == 1440) {
        complete = true;
        line = 0;
        // 图像拼装完成，发射信号
        copy = new uint8_t[size];
        std::memcpy(copy, buffer, size);
        std::cout << "Image Data (first 10 bytes): ";
        for (int i = 0; i < 50; ++i) {
            std::printf("%02x ", copy[i]);
        }
        std::cout << std::endl;
        emit imageReady(copy, width, height, channels); // 传递复制的图像数据
        std::cout<<"send image!"<<std::endl;
        complete=false;
    }

    return true;
}

bool KImageFrame::isComplete() const {
    return complete;
}

uint8_t* KImageFrame::getData() const {
    return buffer;
}
void KImageFrame::reset(){
    complete=false;
}
