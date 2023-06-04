cmake_minimum_required(VERSION 3.20)
project(DStudy)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Tree
        src/tree/main.cc
)

target_include_directories(Tree PUBLIC
        ${CMAKE_SOURCE_DIR}/include/tree
)

add_executable(Sort
        include/algorithm/sort.h
        src/algorithm/sort.cc
        src/algorithm/sort_test.cc
)
target_include_directories(Sort PRIVATE
        include
)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
        target_compile_definitions(Sort PRIVATE
                __DEBUG__
        )
endif()
