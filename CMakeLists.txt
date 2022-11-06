cmake_minimum_required(VERSION 3.22)

project(citadel)

add_library(citadel)

add_subdirectory(source)
add_subdirectory(external/jsoncpp)
add_subdirectory(external/glfw)