cmake_minimum_required(VERSION 3.5) # 设置CMAKE最小版本
project(YouShuangExample_7.1)

set(CMAKE_STANDARD_REQUIRED ON) # C++标准开启
set(CMAKE_CXX_STANDARD 11) # 设置C++的标准为C++11

add_executable(${PROJECT_NAME}_uid # 添加可执行文件
    src/main.cpp
)

target_compile_features(${PROJECT_NAME}_uid PRIVATE cxx_std_11) # 为项目YouShuangExample_5.1.1设置C++11标准
message("cmake system name: " ${CMAKE_SYSTEM_NAME})
