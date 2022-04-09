cmake_minimum_required (VERSION 3.8)

set(TARGET_NAME c_random_nochange)
#设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_ROOT_PATH}/gateway/plugins/collector_plugins/${TARGET_NAME})


aux_source_directory(. compile_list)

ADD_LIBRARY(${TARGET_NAME} SHARED ${compile_list})


include_directories(${THIRD_PARTY_INC_DIR}/boost
					${THIRD_PARTY_INC_DIR}/spdlog)

target_include_directories(${TARGET_NAME}
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
                                   ${PROJECT_INC_DIR}/common)