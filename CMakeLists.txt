#指定最低cmake版本
cmake_minimum_required (VERSION 3.8)

set(CMAKE_TOOLCHAIN_FILE "")

#项目名称
project(Sushine_Gateway)

#判断系统与平台
if(CMAKE_SIZEOF_VOID_P EQUAL 4)
	set(PLATFORM x86)
	set(LIB_PLATFORM lib32)
else()
	set(PLATFORM x64)
	set(LIB_PLATFORM 64)
endif()

message("操作系统是 ${CMAKE_SYSTEM_NAME}")
message("生成平台为 ${PLATFORM}")
message("编译类型为 ${CMAKE_BUILD_TYPE}")

#设置全局cmake变量
set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/third_party)
set(THIRD_PARTY_INC_DIR ${THIRD_PARTY_DIR}/include)
set(THIRD_PARTY_LIB_DIR ${THIRD_PARTY_DIR}/${LIB_PLATFORM}/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE})
set(PROJECT_INC_DIR ${PROJECT_SOURCE_DIR}/include)

set(OUTPUT_ROOT_PATH ${PROJECT_SOURCE_DIR}/${CMAKE_SYSTEM_NAME}/${PLATFORM}/${CMAKE_BUILD_TYPE})

message("THIRD_PARTY_INC_DIR : ${THIRD_PARTY_INC_DIR}")
message("THIRD_PARTY_LIB_DIR : ${THIRD_PARTY_LIB_DIR}")
message("PROJECT_INC_DIR : ${PROJECT_INC_DIR}")

message("程序生成主目录 ${OUTPUT_ROOT_PATH}")
include_directories(${THIRD_PARTY_INC_DIR}/nlohmann)
##添加子目录
add_subdirectory(src)