cmake_minimum_required(VERSION 3.20)
project( ConsoleUtil
    LANGUAGES C CXX CUDA
    VERSION 4
)


file(GLOB PROJ_HEADER_FILES "include/*.h")


set(PROJ_INSTALL_CMAKE_DIR  "${PROJECT_NAME}")


#* 创建一个 header-only target
add_library(${PROJECT_NAME} INTERFACE
	${PROJ_HEADER_FILES}
)

target_compile_definitions(${PROJECT_NAME}
    INTERFACE "CONSOLE_UTIL_VERSION=${PROJECT_VERSION_MAJOR}"
)

target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${PROJECT_NAME}/include>
)

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    INCLUDES DESTINATION ${PROJECT_NAME}/include
)


install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Config.cmake
    # NAMESPACE ${PROJECT_NAME}
    DESTINATION ${PROJ_INSTALL_CMAKE_DIR}
)

install(FILES ${PROJ_HEADER_FILES}
    DESTINATION "${PROJECT_NAME}/include"
    COMPONENT headers
)
