cmake_minimum_required(VERSION 3.20)
project(Test LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options("/utf-8")
add_compile_options("/MP")
add_compile_options("/sdl-")
add_compile_options("/diagnostics:caret")
add_compile_options("/Zc:preprocessor")

set(GTest_DIR "D:/Projects/123/vcpkg_installed/test-triplet/share/gtest")
find_package(GTest REQUIRED)



file(GLOB_RECURSE PROJ_SOURCE_FILES "*.c" "*.cpp")

add_executable(${PROJECT_NAME}
    ${PROJ_SOURCE_FILES}
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		ConsoleUtil
		GTest::gtest
		GTest::gtest_main
)
