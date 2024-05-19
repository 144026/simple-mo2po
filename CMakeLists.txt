cmake_minimum_required(VERSION 3.10)

project(simple-mo2po VERSION 0.3.1)

configure_file(include/config_cmake.h.in include/config_cmake.h)

add_executable(mo2po src/main.c src/mo.c)

target_include_directories(mo2po PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

enable_testing()
set(test_dir ${CMAKE_SOURCE_DIR}/tests)
add_test(
	NAME test1
	COMMAND ${test_dir}/test.sh ${CMAKE_BINARY_DIR}/mo2po ${test_dir}/main.zh.mo ${test_dir}/main.zh.po
)
set_tests_properties(test1 PROPERTIES DEPENDS mo2po)
