cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(GameEngine3d)

set(PROJECT_SOURCE_FILES
    source/main.cpp
    source/Game.hpp
    source/Game.cpp
    source/TestObject.hpp
    source/TestObject.cpp
)

include_directories(engine/thirdparty/glew/include)
include_directories(engine/thirdparty/glm/glm)

include_directories(source)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

# Add GLFW library
add_subdirectory(engine "${CMAKE_CURRENT_BINARY_DIR}/engine_build")
include_directories(engine/source)

include_directories(engine/thirdparty/stb_image)

include_directories(engine/thirdparty/json)

include_directories(thirdparty/cgltf)

# Link engine libraries
target_link_libraries(${PROJECT_NAME}
    Engine
)