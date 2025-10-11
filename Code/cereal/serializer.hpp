#pragma once
#include "serializer.hpp"
#include <sstream>
#include <memory>
#include "archives/json.hpp"
#include "archives/binary.hpp"
#include "types/tuple.hpp"
#include "types/vector.hpp"
#include "types/map.hpp"
#include "types/set.hpp"
#include "types/string.hpp"


namespace lowembed::serialize{

enum class ArchiveType {
    Json,
    Binary
};

class Serializer {
public:
    Serializer(ArchiveType type = ArchiveType::Binary)
        : type_(type) {}

    template<typename T>
    std::string serialize(const T& obj) {
        std::ostringstream os(std::ios::binary);
        if (type_ == ArchiveType::Json) {
            cereal::JSONOutputArchive archive(os);
            archive(obj);
        } else {
            cereal::BinaryOutputArchive archive(os);
            archive(obj);
        }
        return os.str();
    }

    template<typename T>
    T deserialize(const std::string& data) {
        try {
            if (type_ == ArchiveType::Json) {
                if (!data.empty() && data[0] != '{' && data[0] != '[') {
                    throw std::invalid_argument("Invalid JSON format");
                }
                std::istringstream is(data);
                cereal::JSONInputArchive archive(is);
                T obj;
                archive(obj);
                return obj;
            } else {
                // 验证二进制数据的有效性
                if (data.empty()) {
                    throw std::invalid_argument("Empty binary data");
                }
                
                std::istringstream is(data, std::ios::binary);
                // 尝试读取一个字节来验证流的状态
                if (!is || is.peek() == EOF) {
                    throw std::invalid_argument("Invalid binary data stream");
                }
                
                cereal::BinaryInputArchive archive(is);
                T obj;
                archive(obj);

                // 验证是否完全读取了数据
                char extraByte;
                if (is.read(&extraByte, 1)) {
                    throw std::invalid_argument("Extra data after binary serialization");
                }
                
                return obj;
            }
        } catch (const std::exception& e) {
            // 重新抛出所有异常，包括我们自己的验证异常和cereal的异常
            throw;
        }
    }

private:
    ArchiveType type_;
};

#if 0
//JSON 接口
template<typename T>
std::string toJsonString(T obj) {
    Serializer ser(ArchiveType::Json);
    return ser.serialize(std::move(obj));
}

template<typename T>
T fromJsonString(const std::string& data) {
    Serializer ser(ArchiveType::Json);
    return ser.deserialize<T>(data);
}
#endif

template<typename T>
std::string toString(const T& obj) {
    Serializer ser(ArchiveType::Binary);
    return ser.serialize(obj);
}

template<typename T>
T fromString(const std::string& data) {
    Serializer ser(ArchiveType::Binary);
    return ser.deserialize<T>(data);
}

}
