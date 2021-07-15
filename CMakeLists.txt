cmake_minimum_required(VERSION 3.10)

project(simple-mo2po VERSION 0.3.0)

configure_file(include/config_cmake.h.in include/config_cmake.h)

add_executable(mo2po src/main.c src/mo.c)

target_include_directories(mo2po PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

