cmake_minimum_required (VERSION 3.8)

set(TARGET_NAME c_golden)
#设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_ROOT_PATH}/gateway/plugins/collector_plugins/${TARGET_NAME})

include_directories(${THIRD_PARTY_INC_DIR}/boost
					${THIRD_PARTY_INC_DIR}/golden
					${THIRD_PARTY_INC_DIR}/spdlog)

link_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
				${THIRD_PARTY_LIB_DIR}/boost
				${THIRD_PARTY_LIB_DIR}/golden)

aux_source_directory(. compile_list)

ADD_LIBRARY(${TARGET_NAME} SHARED ${compile_list})


target_include_directories(${TARGET_NAME}
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
                                   ${PROJECT_INC_DIR}/common)

								   
if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
	target_link_libraries(${TARGET_NAME} PRIVATE 
		goldenapi)
elseif(${CMAKE_BUILD_TYPE} MATCHES "RelWithDebInfo")
	target_link_libraries(${TARGET_NAME} PRIVATE 
		goldenapi)
endif()
