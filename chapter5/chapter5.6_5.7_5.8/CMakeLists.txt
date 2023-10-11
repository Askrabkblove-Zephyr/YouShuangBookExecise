cmake_minimum_required(VERSION 3.5) # 设置CMAKE最小版本
project(YouShuangExample_5.6)

set(CMAKE_STANDARD_REQUIRED ON) # C++标准开启
set(CMAKE_CXX_STANDARD 11) # 设置C++的标准为C++11

add_executable(${PROJECT_NAME}_client # 添加可执行文件
    src/client.cpp
)

add_executable(${PROJECT_NAME}_server
    src/server.cpp
)

target_compile_features(${PROJECT_NAME}_client PRIVATE cxx_std_11) # 为项目YouShuangExample_5.1.1设置C++11标准
message("cmake system name: " ${CMAKE_SYSTEM_NAME})

target_compile_features(${PROJECT_NAME}_server PRIVATE cxx_std_11) # 为项目YouShuangExample_5.1.1设置C++11标准
message("cmake system name: " ${CMAKE_SYSTEM_NAME})

# if(CMAKE_SYSTEM_NAME STREQUAL Linux)
#     target_include_directories(${PROJECT_NAME} # 指定包含目录
#         PRIVATE
#         ${PROJECT_SOURCE_DIR}/include # 头文件
#         ${PROJECT_SOURCE_DIR}/src # 资源文件
#     )
# endif()