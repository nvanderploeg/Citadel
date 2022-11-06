cmake_minimum_required(VERSION 3.22)

target_include_directories(${PROJECT_NAME}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)


target_sources(${PROJECT_NAME}
PRIVATE
citadelDef.h
clock.cpp
clock.h
cTime.cpp
cTime.h
JSONSerializable.h
resourcePath.h
serializer.cpp
serializer.h
tickable.h
types.h
windowProperties.cpp
windowProperties.h
)