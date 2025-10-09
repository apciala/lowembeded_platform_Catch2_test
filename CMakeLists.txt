cmake_minimum_required(VERSION 3.5)
project(lowembeded_platform_Catch2_test)

# 查找Catch2
find_package(Catch2 REQUIRED)

# 添加测试可执行文件
add_executable(test tests/unit/main.cpp)
target_link_libraries(test PRIVATE Catch2::Catch2)

add_executable(test2 tests/unit/test.cpp)

include_directories(Code)