#include "../../Code/cereal/serializer.hpp"
#include "../integration/binary_utils.hpp"
#include <iostream>

int main() {
    // 测试对象
    int testValue = 12345;
    std::vector<int> testVec = {1, 2, 3, 4, 5};

    // 二进制序列化
    lowembed::serialize::Serializer binarySer(lowembed::serialize::ArchiveType::Binary);
    std::string binaryData1 = binarySer.serialize(testValue);
    std::string binaryData2 = binarySer.serialize(testVec);

    // JSON序列化（作为对比）
    lowembed::serialize::Serializer jsonSer(lowembed::serialize::ArchiveType::Json);
    std::string jsonData = jsonSer.serialize(testValue);

    // 1. 检测是否为二进制数据
    std::cout << "Is binaryData1 binary? " << std::boolalpha 
              << lowembed::serialize::utils::isBinaryData(binaryData1) << "\n"; // 预期true
    std::cout << "Is jsonData binary? " 
              << lowembed::serialize::utils::isBinaryData(jsonData) << "\n\n"; // 预期false

    // 2. 查看二进制数据（十六进制格式）
    std::cout << "binaryData1 (hex): " 
              << lowembed::serialize::utils::binaryToHex(binaryData1) << "\n";
    std::cout << "binaryData2 (hex): " 
              << lowembed::serialize::utils::binaryToHex(binaryData2) << "\n\n";

    // 3. 查看二进制数据（二进制位格式）
    std::cout << "binaryData1 (bits): " 
              << lowembed::serialize::utils::binaryToBits(binaryData1) << "\n";

    return 0;
}