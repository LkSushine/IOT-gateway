#指定最低cmake版本
cmake_minimum_required (VERSION 3.8)

#指定C++标准
#set(CMAKE_CXX_STANDARD 17)

#设置操作系统预定义
if(WIN32)
	add_definitions(
	"-std:c++17"
	-D_WIN32_WINNT=0x0601
)
else()
endif()

#添加子目录
add_subdirectory(gateway)
