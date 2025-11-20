cmake_minimum_required(VERSION 3.10)

project(GameEngine3d)

set(PROJECT_SOURCE_FILES
    source/main.cpp
)

include_directories(source)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

# Add GLFW library
add_subdirectory(engine "${CMAKE_CURRENT_BINARY_DIR}/engine_build")

# Link engine libraries
target_link_libraries(${PROJECT_NAME}
    Engine
)