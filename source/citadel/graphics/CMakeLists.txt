cmake_minimum_required(VERSION 3.22)

target_include_directories(${PROJECT_NAME}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(files
camera.cpp
camera.h
formatSupport.cpp
formatSupport.h
graphics.cpp
graphics.h
imageView.cpp
imageView.h
meshData.h
queueFamily.cpp
queueFamily.h
renderer.cpp
renderer.h
shader.cpp
shader.h
swapchain.cpp
swapchain.h
texture.h
vertex.h
CMakeLists.txt
)

target_sources(${PROJECT_NAME}
PRIVATE
${files}
)

source_group(graphics FILES ${files})
