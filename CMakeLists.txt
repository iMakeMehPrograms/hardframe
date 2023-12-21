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

# Local Libraries

# Utilities 
# General Utilities
add_library(${PROJECT_NAME}-general-utility STATIC)
target_include_directories(${PROJECT_NAME}-general-utility PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/include
    # /usr/local/include/hardframe/utility/general.hpp
)
target_sources(${PROJECT_NAME}-general-utility PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/source/utility/funcs/general.cpp
)

# Spatial Utilities
add_library(${PROJECT_NAME}-spatial-utility STATIC)
target_include_directories(${PROJECT_NAME}-spatial-utility PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/include
    # /usr/local/include/hardframe/utility/spatial.hpp
)
target_sources(${PROJECT_NAME}-spatial-utility PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/source/utility/types/transform.cpp
)

# Loadable Utilities
add_library(${PROJECT_NAME}-load-utility STATIC)
target_include_directories(${PROJECT_NAME}-load-utility PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/include
    # /usr/local/include/hardframe/utility/loadable.hpp
)
target_sources(${PROJECT_NAME}-load-utility PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/source/utility/types/loadable.cpp
)

# Graphics
add_library(${PROJECT_NAME}-base-graphics STATIC)
target_include_directories(${PROJECT_NAME}-base-graphics PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/include
    # /usr/local/include/hardframe/utility/general.hpp
)
target_sources(${PROJECT_NAME}-base-graphics PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/source/graphics/opgl/base/abstracts.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/source/graphics/opgl/base/assets.cpp
)

# Binary Stuff
add_executable(${PROJECT_NAME}-test project/main.cpp)

# Add Libraries
target_link_libraries(${PROJECT_NAME}-test PUBLIC ${PROJECT_NAME}-general-utility)