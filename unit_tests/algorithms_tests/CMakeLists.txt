cmake_minimum_required(VERSION 3.2)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(runAlgorithmTests
        kd_tree_test.cpp
        vp_tree_test.cpp
        bbf_tree_test.cpp
        lsh_test.cpp
        cluster_test.cpp
        linear_test.cpp
        clustering_test.cpp)

target_link_libraries(runAlgorithmTests gtest gtest_main)
target_link_libraries(runAlgorithmTests algorithms)
