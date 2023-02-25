cmake_minimum_required(VERSION 3.22)

target_include_directories(${PROJECT_NAME}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(ecs)
add_subdirectory(game)
add_subdirectory(graphics)
add_subdirectory(gui)
add_subdirectory(input)
add_subdirectory(system)