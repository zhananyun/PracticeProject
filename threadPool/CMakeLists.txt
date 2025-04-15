# 设置最小的CMake版本
cmake_minimum_required(VERSION 3.10)
# 设置项目名称和版本
project(ThreadPool VERSION 1.0)
# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 添加可执行文件
add_executable(thread_pool_app main.cpp thread_pool.cpp)
# 链接pthread库
find_package(Threads REQUIRED)
target_link_libraries(thread_pool_app PRIVATE Threads::Threads)
