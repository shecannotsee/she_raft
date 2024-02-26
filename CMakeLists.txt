########################################################################################################################
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "she_raft")
set(CMAKE_CXX_FLAGS "-g")# 断点无效处理方案
project(${PROJECT_NAME})

# include
include_directories(${CMAKE_SOURCE_DIR}/src)
# lib
link_directories()

file(GLOB_RECURSE SRC "${CMAKE_SOURCE_DIR}/src/*")
add_executable(${PROJECT_NAME} ${SRC})

# 链接库
target_link_libraries(${PROJECT_NAME} "-pthread")

########################################################################################################################
