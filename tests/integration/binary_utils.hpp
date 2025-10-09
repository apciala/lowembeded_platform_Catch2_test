#pragma once
#include <string>
#include <iomanip>
#include <sstream>
#include <cctype>

namespace lowembed::serialize::utils {

// 检测字符串是否包含二进制特征（不可打印字符）
bool isBinaryData(const std::string& data) {
    for (char c : data) {
        // 检查是否为不可打印ASCII字符（0-31或127）
        if (static_cast<unsigned char>(c) < 32 || static_cast<unsigned char>(c) == 127) {
            return true;
        }
    }
    return false;
}

// 将二进制数据转换为十六进制字符串（便于查看）
std::string binaryToHex(const std::string& data, bool uppercase = true, const std::string& separator = " ") {
    std::stringstream ss;
    ss << std::setfill('0') << std::hex;
    if (uppercase) {
        ss << std::uppercase;
    }
    
    for (size_t i = 0; i < data.size(); ++i) {
        // 每个字节转换为2位十六进制
        ss << std::setw(2) << static_cast<int>(static_cast<unsigned char>(data[i]));
        if (i != data.size() - 1) {
            ss << separator;
        }
    }
    return ss.str();
}

// 将二进制数据转换为二进制位字符串（8位一组）
std::string binaryToBits(const std::string& data, const std::string& separator = " ") {
    std::stringstream ss;
    for (size_t i = 0; i < data.size(); ++i) {
        unsigned char c = static_cast<unsigned char>(data[i]);
        // 从高位到低位输出8位二进制
        for (int bit = 7; bit >= 0; --bit) {
            ss << ((c >> bit) & 1);
        }
        if (i != data.size() - 1) {
            ss << separator;
        }
    }
    return ss.str();
}

} // namespace lowembed::serialize::utils
