
#最低版本要求
cmake_minimum_required (VERSION 2.8)

#系统类型
set(CMAKE_SYSTEM_NAME Linux)

#使用交叉编译器?
#set(CROSS_COMPILE "arm-linux-gnueabihf-")
set(CROSS_COMPILE "")

#指定编译器
set(CMAKE_C_COMPILER "${CROSS_COMPILE}gcc")
set(CMAKE_CXX_COMPILER "${CROSS_COMPILE}g++")

#项目名称
project (opencvTest)

#指定源文件目录
aux_source_directory(${CMAKE_SOURCE_DIR} src)

find_package(OpenCV REQUIRED)
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

#添加 INC LIB
include_directories("${CMAKE_SOURCE_DIR}/inc" ${OpenCV_INCLUDE_DIRS})

#app对应源文件 指定依赖库
add_executable(app ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_link_libraries(app ${OpenCV_LIBS})
