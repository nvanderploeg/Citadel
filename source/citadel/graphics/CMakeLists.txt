cmake_minimum_required(VERSION 3.22)

target_include_directories(${PROJECT_NAME}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
set(folderName "Graphics")

set(files
camera.cpp
camera.h
graphics.cpp
graphics.h
shader.cpp
shader.h
vertex.h
CMakeLists.txt
)

target_sources(${PROJECT_NAME}
PRIVATE
${files}
)

source_group($(folderName) FILES ${files})
