cmake_minimum_required(VERSION 3.22)

target_include_directories(${PROJECT_NAME}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)


target_sources(${PROJECT_NAME}
PRIVATE
GUI.h
GUIButton.cpp
GUIButton.hpp
GUIConstraint.hpp
GUIEnvironment.cpp
GUIEnvironment.hpp
GUIObject.cpp
GUIObject.hpp
GUIPanel.cpp
GUIPanel.hpp
GUIRenderObject.cpp
GUIRenderObject.hpp
)