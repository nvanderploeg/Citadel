cmake_minimum_required(VERSION 3.22)

target_include_directories(${PROJECT_NAME}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)


target_sources(${PROJECT_NAME}
PRIVATE
entity.h
component.h
componentPool.h
componentPool.cpp
filter.h
registry.h
registry.cpp
)