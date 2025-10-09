#define CATCH_CONFIG_MAIN  // 提供main函数
#include <catch2/catch.hpp>
#include <string>
#include "../../Code/cereal/serializer.hpp"  // 包含你的序列化头文件



TEST_CASE("Serializer basic functionality", "[serializer]") {
    using namespace lowembed::serialize;
    
    SECTION("Binary serialization - primitive types") {
        Serializer serializer(ArchiveType::Binary);
        
        // 测试整数序列化
        int originalInt = 42;
        auto serializedInt = serializer.serialize(originalInt);
        auto deserializedInt = serializer.deserialize<int>(serializedInt);
        REQUIRE(originalInt == deserializedInt);
        
        // 测试浮点数序列化
        double originalDouble = 3.14159;
        auto serializedDouble = serializer.serialize(originalDouble);
        auto deserializedDouble = serializer.deserialize<double>(serializedDouble);
        REQUIRE(originalDouble == Approx(deserializedDouble));
    }
    
    SECTION("Binary serialization - string") {
        Serializer serializer(ArchiveType::Binary);
        
        std::string originalStr = "Hello, Catch2!";
        auto serializedStr = serializer.serialize(originalStr);
        auto deserializedStr = serializer.deserialize<std::string>(serializedStr);
        REQUIRE(originalStr == deserializedStr);
    }
    
    SECTION("Binary serialization - vector") {
        Serializer serializer(ArchiveType::Binary);
        
        std::vector<int> originalVec = {1, 2, 3, 4, 5};
        auto serializedVec = serializer.serialize(originalVec);
        auto deserializedVec = serializer.deserialize<std::vector<int>>(serializedVec);
        REQUIRE(originalVec == deserializedVec);
    }
    
    SECTION("Binary serialization - map") {
        Serializer serializer(ArchiveType::Binary);
        
        std::map<std::string, int> originalMap = {{"one", 1}, {"two", 2}, {"three", 3}};
        auto serializedMap = serializer.serialize(originalMap);
        auto deserializedMap = serializer.deserialize<std::map<std::string, int>>(serializedMap);
        REQUIRE(originalMap == deserializedMap);
    }
    
    SECTION("Json serialization - basic types") {
        Serializer serializer(ArchiveType::Json);
        
        // 测试整数序列化
        int originalInt = 42;
        auto serializedInt = serializer.serialize(originalInt);
        auto deserializedInt = serializer.deserialize<int>(serializedInt);
        REQUIRE(originalInt == deserializedInt);
        
        // 测试字符串序列化
        std::string originalStr = "Test JSON serialization";
        auto serializedStr = serializer.serialize(originalStr);
        auto deserializedStr = serializer.deserialize<std::string>(serializedStr);
        REQUIRE(originalStr == deserializedStr);
    }
    
    SECTION("Convenience functions - toString/fromString") {
        // 测试便捷函数
        std::vector<std::string> originalVec = {"apple", "banana", "cherry"};
        double a = 3.14159;
        auto serialized = toString(originalVec);
        auto deserialized = fromString<std::vector<std::string>>(serialized);
        REQUIRE(originalVec == deserialized);
    }
}

TEST_CASE("Serializer edge cases", "[serializer][edge]") {
    using namespace lowembed::serialize;
    
    SECTION("Empty string serialization") {
        Serializer serializer(ArchiveType::Binary);
        
        std::string emptyStr;
        auto serialized = serializer.serialize(emptyStr);
        auto deserialized = serializer.deserialize<std::string>(serialized);
        REQUIRE(deserialized.empty());
    }
    
    SECTION("Empty container serialization") {
        Serializer serializer(ArchiveType::Binary);
        
        std::vector<int> emptyVec;
        auto serialized = serializer.serialize(emptyVec);
        auto deserialized = serializer.deserialize<std::vector<int>>(serialized);
        REQUIRE(deserialized.empty());
    }
    
    SECTION("Invalid deserialization") {
        Serializer serializer(ArchiveType::Binary);
        
        std::string invalidData = "This is not a serialized data";
        REQUIRE_THROWS_AS(serializer.deserialize<int>(invalidData), std::exception);
    }
}
