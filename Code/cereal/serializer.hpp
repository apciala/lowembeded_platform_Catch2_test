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
        if (type_ == ArchiveType::Json) {
            std::istringstream is(data);
            cereal::JSONInputArchive archive(is);
            T obj;
            archive(obj);
            return obj;
        } else {
            std::istringstream is(data, std::ios::binary);
            cereal::BinaryInputArchive archive(is);
            T obj;
            archive(obj);
            return obj;
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
std::string toString(T obj) {
    Serializer ser(ArchiveType::Binary);
    return ser.serialize(std::move(obj));
}

template<typename T>
T fromString(const std::string& data) {
    Serializer ser(ArchiveType::Binary);
    return ser.deserialize<T>(data);
}

}
