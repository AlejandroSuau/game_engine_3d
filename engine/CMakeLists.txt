cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Engine)

set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")

configure_file(
    ${PROJECT_SOURCE_DIR}/config.h.in
    ${PROJECT_BINARY_DIR}/config.h
)

set(PROJECT_SOURCE_FILES
    source/Engine.hpp
    source/Engine.cpp
    source/Application.hpp
    source/Application.cpp
    source/input/InputManager.hpp
    source/input/InputManager.cpp
    source/graphics/ShaderProgram.hpp
    source/graphics/ShaderProgram.cpp
    source/graphics/GraphicsAPI.hpp
    source/graphics/GraphicsAPI.cpp
    source/graphics/VertexLayout.hpp
    source/graphics/Texture.hpp
    source/graphics/Texture.cpp
    source/render/Material.hpp
    source/render/Material.cpp
    source/render/Mesh.hpp
    source/render/Mesh.cpp
    source/render/RenderQueue.hpp
    source/render/RenderQueue.cpp
    source/scene/GameObject.hpp
    source/scene/GameObject.cpp
    source/scene/Scene.hpp
    source/scene/Scene.cpp
    source/scene/Component.hpp
    source/scene/Component.cpp
    source/scene/components/MeshComponent.hpp
    source/scene/components/MeshComponent.cpp
    source/scene/components/CameraComponent.hpp
    source/scene/components/CameraComponent.cpp
    source/scene/components/PlayerControllerComponent.hpp
    source/scene/components/PlayerControllerComponent.cpp
    source/scene/components/LightComponent.hpp
    source/scene/components/LightComponent.cpp
    source/scene/components/AnimationComponent.hpp
    source/scene/components/AnimationComponent.cpp
    source/scene/components/PhysicsComponent.hpp
    source/scene/components/PhysicsComponent.cpp
    source/scene/components/AudioComponent.hpp
    source/scene/components/AudioComponent.cpp
    source/scene/components/AudioListenerComponent.hpp
    source/scene/components/AudioListenerComponent.cpp
    source/io/FileSystem.hpp
    source/io/FileSystem.cpp
    source/physics/PhysicsManager.hpp
    source/physics/PhysicsManager.cpp
    source/physics/Collider.hpp
    source/physics/Collider.cpp
    source/physics/RigidBody.hpp
    source/physics/RigidBody.cpp
    source/physics/KinematicCharacterController.hpp
    source/physics/KinematicCharacterController.cpp
    source/audio/AudioManager.hpp
    source/audio/AudioManager.cpp    
    source/audio/Audio.hpp
    source/audio/Audio.cpp
    source/EngineCommon.hpp
)

include_directories(source)
add_library(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

# Add GLFW library
add_subdirectory(thirdparty/glfw-3.4 "${CMAKE_CURRENT_BINARY_DIR}/glfw_build")
include_directories(thirdparty/glfw-3.4/include)

# Add Glew library
set(BUILD_UTILS OFF CACHE BOOL "utilities" FORCE)
add_subdirectory(thirdparty/glew/build/cmake "${CMAKE_CURRENT_BINARY_DIR}/glew_build")
include_directories(thirdparty/glew/include)
set_property(TARGET glew_s PROPERTY FOLDER GLEW)
set_property(TARGET glew   PROPERTY FOLDER GLEW)

# Add GLM (header-only)
add_subdirectory(thirdparty/glm "${CMAKE_CURRENT_BINARY_DIR}/glm_build")
include_directories(thirdparty/glm/glm)

# STB Image
include_directories(thirdparty/stb_image)

# nlohman json
include_directories(thirdparty/json)

include_directories(thirdparty/cgltf)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_BINARY_DIR})

add_library(miniaudio INTERFACE)
target_include_directories(miniaudio INTERFACE thirdparty/miniaudio)

if(UNIX AND NOT APPLE)
    target_link_libraries(miniaudio INTERFACE dl pthread m)
endif()

if(WIN32)
    target_link_libraries(miniaudio INTERFACE winmm user32 ole32)
endif()

if(APPLE)
    find_library(COREAUDIO_FRAMEWORK CoreAudio)
    find_library(AUDIOTOOLBOX_FRAMEWORK AudioToolbox)
    find_library(AUDIOUNIT_FRAMEWORK AudioUnit)
    find_library(COREFOUNDATION_FRAMEWORK CoreFoundation)
    target_link_libraries(miniaudio INTERFACE
        ${COREAUDIO_FRAMEWORK}
        ${AUDIOTOOLBOX_FRAMEWORK}
        ${AUDIOUNIT_FRAMEWORK}
        ${COREFOUNDATION_FRAMEWORK}
    )
endif()

# Include Bullet as subdirectory
option(BUILD_UNIT_TESTS OFF)
option(BUILD_BULLET2_DEMOS OFF)
option(BUILD_EXTRAS OFF)
option(BUILD_SHARED_LIBS OFF)
add_subdirectory(thirdparty/bullet3-3.25)
target_include_directories(${PROJECT_NAME} PRIVATE thirdparty/bullet3-3.25/src)

# Link all thirdparty libraries
target_link_libraries(${PROJECT_NAME}
    glfw
    glew_s
    glm
    LinearMath
    BulletCollision
    BulletDynamics
    miniaudio
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${ASSETS_DIR}
    ${CMAKE_BINARY_DIR}/assets
)