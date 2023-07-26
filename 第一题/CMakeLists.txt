cmake_minimum_required(VERSION 3.0)
project(main)

# 设置C++编译标准
set(CMAKE_CXX_STANDARD 11)

# 查找Opencv
find_package(OpenCV REQUIRED)

# 添加一个用于包含的文件去构建的文件夹
include_directories( ${OpenCV_INCLUDE_DIRS} ) 

# 添加可执行文件
add_executable(main main.cpp)

# 链接OpenCV库
target_link_libraries(main ${OpenCV_LIBS})
