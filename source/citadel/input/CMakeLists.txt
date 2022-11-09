cmake_minimum_required(VERSION 3.22)

target_include_directories(${PROJECT_NAME}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)


target_sources(${PROJECT_NAME}
PRIVATE
input.h
inputContext.h
inputContext.cpp
inputRouter.cpp
inputRouter.h
)