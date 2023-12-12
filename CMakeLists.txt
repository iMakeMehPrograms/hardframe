cmake_minimum_required(VERSION 3.24.2 FATAL_ERROR)

project(hardframe)
set(PROJECT_VERSION 0.0)
set(PROJECT_DESCRIPTION "Hardframe is a game and demo-making framework with 3d graphics, physics and more.")
set(LANGUAGE CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(${PROJECT_NAME}-utility STATIC)
target_include_directories(${PROJECT_NAME}-utility PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/include
    # /usr/local/include/hardframe/utility/utility.hpp
)
target_sources(${PROJECT_NAME}-utility PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/source/utility/types/transform.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/source/utility/types/loadable.cpp
)

add_executable(${PROJECT_NAME}-test project/main.cpp)
target_link_libraries(${PROJECT_NAME}-test PUBLIC ${PROJECT_NAME}-utility)