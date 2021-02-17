cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(network-monitor)

# Dependencies
# If dependencies are managed with conan, we prepend the current build folder
# to the CMake module path, where CMake looks for dependencies.
if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/conaninfo.txt)
    list(PREPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_BINARY_DIR}")    
endif()
find_package(Boost 1.75 REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)

# Static library
set(LIB_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/WebSocketClient.cpp"
)
add_library(network-monitor-lib STATIC ${LIB_SOURCES})

target_compile_features(network-monitor-lib
    PUBLIC 
        cxx_std_14
)

target_include_directories(network-monitor-lib
    PUBLIC
        inc
)

target_link_libraries(network-monitor-lib
    PUBLIC
        Boost::Boost
        OpenSSL::OpenSSL
)

# Test area
set(TEST_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/websocket-client.cpp"
)
add_executable(network-monitor-tests ${TEST_SOURCES})

target_compile_features(network-monitor-tests
    PRIVATE 
        cxx_std_14
)

target_link_libraries(network-monitor-tests
    PRIVATE
        network-monitor-lib
        Boost::Boost
)