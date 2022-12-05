cmake_minimum_required(VERSION 3.22)

target_include_directories(${PROJECT_NAME}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(${PROJECT_NAME}
PRIVATE
citadelGame.cpp
citadelGame.h
gameConfig.cpp
gameConfig.h
gameObject.cpp
gameObject.h
scene.cpp
scene.h
)
