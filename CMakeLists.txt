cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(network-monitor)

if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/conanfile.py)
    list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})    
endif()


set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_executable(network-monitor ${SOURCE})

target_compile_features(
    network-monitor PRIVATE cxx_std_11   
)