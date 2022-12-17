cmake_minimum_required(VERSION 3.22)

project(citadel VERSION 0.1 
                DESCRIPTION "Engine for making Games"
                LANGUAGES CXX)

# find_package(vulkan REQUIRED)

set(GLFW_BUILD_DOCS, OFF)
add_library(citadel STATIC)

add_subdirectory(source)
add_subdirectory(external/jsoncpp)
add_subdirectory(external/glfw)
add_subdirectory(external/glm)
add_subdirectory(external/tinyobjloader)

add_dependencies(citadel glfw glm tinyobjloader)

if(APPLE) 
    target_link_libraries(citadel PUBLIC glfw glm vulkan tinyobjloader)
    set(VULKAN_SDK_DIR $ENV{VULKAN_SDK_PATH})
    target_include_directories(${PROJECT_NAME} PUBLIC
        ${VULKAN_SDK_DIR}/macOS/include
    )

    target_link_directories(${PROJECT_NAME} PUBLIC
        ${VULKAN_SDK_DIR}/macOS/lib
    )
elseif(MSVC)
    target_link_libraries(citadel PUBLIC glfw glm vulkan-1 tinyobjloader)
    set(VULKAN_SDK_DIR $ENV{VK_SDK_PATH})
    target_include_directories(${PROJECT_NAME} PUBLIC
        ${VULKAN_SDK_DIR}/Include
    )

    target_link_directories(${PROJECT_NAME} PUBLIC
        ${VULKAN_SDK_DIR}/Lib
    )
else()
    target_link_libraries(citadel PUBLIC glfw glm vulkan tinyobjloader)
    # target_link_libraries(citadel PUBLIC vulkan)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/external/stb

)