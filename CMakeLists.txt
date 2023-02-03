cmake_minimum_required(VERSION 3.25)
project(tcp-tun LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)

file(GLOB LIBCORE_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp)
list(REMOVE_ITEM LIBCORE_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Source/main.cpp")
file(GLOB LIBCORE_INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.h)
add_library(${PROJECT_NAME}-core SHARED
        ${LIBCORE_SOURCE_FILES}
        ${LIBCORE_INCLUDE_FILES}
        )
add_library(core::private::${PROJECT_NAME} ALIAS ${PROJECT_NAME}-core)
target_include_directories(${PROJECT_NAME}-core
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
        )

file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp)
file(GLOB INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.h)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Include)
find_package(fmt)
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${INCLUDE_FILES})
target_link_libraries(${PROJECT_NAME} fmt::fmt)
add_subdirectory(Test)