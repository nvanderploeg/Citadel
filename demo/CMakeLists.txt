cmake_minimum_required(VERSION 3.22)

#setting c++ to c++20 
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(CitaDemo VERSION 0.1)

#xcode and MSVC are troublesome, so we set it as a cxxflag as well
if (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT CitaDemo)
endif(MSVC)

#example of setting paths
#set(SOURCE_PATH ${CMAKE_CURRENT_LIST_DIR}/source)

#Elementia Project, create executable targer
add_executable(CitaDemo)

#example setting other compile flags to the Elementia Target
#set_property (TARGET Elementia APPEND_STRING PROPERTY 
#COMPILE_FLAGS "-DBUILD_RESOURCE_PATH=1")

#adding Citadel engine
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_BINARY_DIR}/citadel)
                                                
# We need to build citadel for Elementia to build!
add_dependencies(CitaDemo citadel)

# and we need to link to citadel and it's dependancies
target_link_libraries(CitaDemo
    PUBLIC
    citadel
)

#Example if we wanted to add manual include paths here
# target_include_directories(Elementia
# PRIVATE
# )


target_sources(CitaDemo
PRIVATE
citaDemo/main.cpp
citaDemo/demoGame.cpp
citaDemo/demoGame.h
citaDemo/demoScene.cpp
citaDemo/demoScene.h
)

execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/textures
                                                           ${CMAKE_BINARY_DIR}/textures)


execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/shaders
                                                           ${CMAKE_BINARY_DIR}/shaders)


execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/models
                                                           ${CMAKE_BINARY_DIR}/models)