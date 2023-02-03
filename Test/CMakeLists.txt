cmake_minimum_required(VERSION 3.25)
project(test LANGUAGES CXX)

enable_testing()
find_package(GTest REQUIRED)
file(GLOB TEST_FILES *.cpp)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} ${TEST_FILES})
target_link_libraries(${PROJECT_NAME}
        PRIVATE core::private::tcp-tun
        ${GTEST_LIBRARIES}
        fmt::fmt
        )