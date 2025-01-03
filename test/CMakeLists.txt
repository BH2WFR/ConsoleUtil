cmake_minimum_required(VERSION 3.20)
project(Test LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	add_compile_options("/utf-8")
	add_compile_options("/MP")
	add_compile_options("/sdl-")
	add_compile_options("/diagnostics:caret")
	add_compile_options("/Zc:preprocessor")
	add_compile_options("/fsanitize=address")
else()
	# add_compile_options("-std=c++2b")
	add_compile_options("-fno-omit-frame-pointer")
	# add_compile_options("-fsanitize=address")
	# add_compile_options("-fsanitize=leak")
	# add_compile_options("-fsanitize=undefined")
	# add_compile_options("-fsanitize=pointer-compare")
	# add_compile_options("-fsanitize=pointer-subtract")
	# add_compile_options("-fsanitize=shift")
	# add_compile_options("-fsanitize=integer-divide-by-zero")
	# add_compile_options("-fsanitize=unreachable")
	# add_compile_options("-fsanitize=vla-bound")
	# add_compile_options("-fsanitize=null")
	# add_compile_options("-fsanitize=return")
	# add_compile_options("-fsanitize=bounds")
	# add_compile_options("-fsanitize=bounds-strict")
	# add_compile_options("-fsanitize=alignment")
	# add_compile_options("-fsanitize=object-size")
	# add_compile_options("-fsanitize=float-divide-by-zero")
	# add_compile_options("-fsanitize=float-cast-overflow")
	# add_compile_options("-fsanitize=nonnull-attribute")
	# add_compile_options("-fsanitize=returns-nonnull-attribute")
	# add_compile_options("-fsanitize=bool")
	# add_compile_options("-fsanitize=enum")
	# add_compile_options("-fsanitize=vptr")
	# add_compile_options("-fsanitize=pointer-overflow")
endif()

set(GTest_DIR "D:/Projects/123/vcpkg_installed/test-triplet-asan/share/gtest")
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
