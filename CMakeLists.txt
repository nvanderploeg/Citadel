cmake_minimum_required(VERSION 3.22)

project(citadel VERSION 0.1 
                DESCRIPTION "Engine for making 2D Games"
                LANGUAGES CXX)

find_package(OpenGL REQUIRED)

add_library(citadel STATIC)

add_subdirectory(source)
add_subdirectory(external/jsoncpp)
add_subdirectory(external/glfw)

add_dependencies(citadel glfw)


target_include_directories(${PROJECT_NAME}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/include
)