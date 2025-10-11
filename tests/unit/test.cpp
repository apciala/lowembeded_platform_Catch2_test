#include "../../Code/cereal/serializer.hpp"
#include "../integration/binary_utils.hpp"
#include <iostream>

// 将整数以小端形式追加到字符串
template<typename Int>
void append_le(std::string &out, Int v) {
    for (size_t i = 0; i < sizeof(Int); ++i) {
        out.push_back(static_cast<char>((static_cast<uint64_t>(v) >> (8*i)) & 0xFF));
    }
}

int main() {
    // 测试对象
    int testValue = 12345;
    //std::vector<int> testVec = {1, 2, 3, 4, 5};
    std::string testVec = "Hello, World!6666666666666666666666";

    // 目标字符串（你的例子）
    std::string target = "World666";

    // 手工构造二进制归档：先写长度（uint64_t 小端），再写数据 bytes
    std::string handcrafted;
    append_le<uint64_t>(handcrafted, static_cast<uint64_t>(target.size()));
    handcrafted += "World679";
    std::string originstr = lowembed::serialize::fromString<std::string>(handcrafted);
    std::cout << "Origin string: " << originstr << "\n\n";

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