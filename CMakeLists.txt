cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(network-monitor)

# Add the local CMake modules folder to the CMake search path.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Dependencies
# If dependencies are managed with conan, we prepend the current build folder
# to the CMake module path, where CMake looks for dependencies.
if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/conaninfo.txt)
    list(PREPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_BINARY_DIR}")    
endif()
find_package(Boost 1.75 REQUIRED COMPONENTS system)
find_package(Filesystem REQUIRED)
find_package(OpenSSL REQUIRED)

# Called before any other target is defined.
enable_testing()

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
        cxx_std_17
)

# Hardcode the cacert.pem location in the network-monitor-tests executable (not recommended)
target_compile_definitions(network-monitor-tests
    PRIVATE
        TESTS_CACERT_PEM="${CMAKE_CURRENT_SOURCE_DIR}/tests/cacert.pem"
)

target_link_libraries(network-monitor-tests
    PRIVATE
        network-monitor-lib
        Boost::Boost
        std::filesystem
)

add_test(
    NAME network-monitor-tests
    COMMAND $<TARGET_FILE:network-monitor-tests>
)

# This tells CMake to check for a specific output to verify the test outcome.
# When all unit tests pass, Boost.Test prints "No errors detected".
set_tests_properties(network-monitor-tests PROPERTIES
    PASS_REGULAR_EXPRESSION ".*No errors detected"
)