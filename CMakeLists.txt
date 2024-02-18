cmake_minimum_required(VERSION 3.24.2 FATAL_ERROR)

set(CMAKE_MESSAGE_LOG_LEVEL DEBUG)

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
add_compile_options("-g")

# External Libraries
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

set(glm_DIR /usr/local/lib/cmake/glm)
find_package(glm REQUIRED)
target_include_directories(glm::glm INTERFACE "/usr/local/include")

message(STATUS "SDL2 Found: ${SDL2_FOUND}")
message(DEBUG "SDL2 Location: ${SDL2_INCLUDE_DIR}")
message(DEBUG "SDL2 Libs: ${SDL2_LIBRARIES}")
message(STATUS "")

message(STATUS "OpenGL Found: ${OPENGL_FOUND}")
message(DEBUG "OpenGL Location: ${OPENGL_INCLUDE_DIR}")
message(DEBUG "OpenGL Libs: ${OPENGL_LIBRARIES}")
message(STATUS "")

message(STATUS "GLEW Found: ${GLEW_FOUND}")
message(STATUS "GLEW Version: ${GLEW_VERSION}")
message(DEBUG "GLEW Location: ${GLEW_INCLUDE_DIR}")
message(DEBUG "GLEW Libs: ${GLEW_LIBRARIES}")
message(STATUS "")

message(STATUS "GLM Found: ${GLM_FOUND}")
message(DEBUG "GLM Location: ${GLM_INCLUDE_DIRS}")
message(STATUS "")

message(VERBOSE "Building externs...")
message(VERBOSE "")

# Extern-Local Libraries
add_library(nothings-stb INTERFACE)
target_include_directories(nothings-stb INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/extern/stb/include
)

message(VERBOSE "Building Utilities...")
message(VERBOSE "")

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
target_link_libraries(${PROJECT_NAME}-spatial-utility glm::glm)

# Loadable Utilities
add_library(${PROJECT_NAME}-load-utility STATIC)
target_include_directories(${PROJECT_NAME}-load-utility PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/include
    # /usr/local/include/hardframe/utility/loadable.hpp
)
target_sources(${PROJECT_NAME}-load-utility PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/source/utility/types/loadable.cpp
)

# Debugging Utilities
add_library(${PROJECT_NAME}-debug-utility STATIC)
target_include_directories(
    ${PROJECT_NAME}-debug-utility PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/include
    /usr/local/include/hardframe/utility/loadable.hpp
)
target_sources(${PROJECT_NAME}-debug-utility PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/source/utility/funcs/debug.cpp
)

message(VERBOSE "Building Graphics...")
message(VERBOSE "")

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
target_link_libraries(${PROJECT_NAME}-base-graphics ${PROJECT_NAME}-spatial-utility ${PROJECT_NAME}-load-utility ${PROJECT_NAME}-debug-utility ${PROJECT_NAME}-general-utility)
target_link_libraries(${PROJECT_NAME}-base-graphics nothings-stb)
target_link_libraries(${PROJECT_NAME}-base-graphics SDL2::SDL2 OpenGL::GL OpenGL::GLU GLEW::glew)

# Binary Stuff
add_executable(${PROJECT_NAME}-test project/main.cpp)

# Add Libraries
target_link_libraries(${PROJECT_NAME}-test PUBLIC ${PROJECT_NAME}-general-utility ${PROJECT_NAME}-base-graphics ${PROJECT_NAME}-debug-utility)
