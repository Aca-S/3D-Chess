cmake_minimum_required(VERSION 3.17)
project(rg_3d_sah)

set(CMAKE_CXX_STANDARD 14)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(ASSIMP REQUIRED)

add_subdirectory(libs/glad/)
add_subdirectory(libs/stb/)

add_executable(rg_3d_sah src/main.cpp classes/Shader.cpp classes/Shader.h classes/Texture2D.cpp classes/Texture2D.h classes/error.h classes/Camera.cpp classes/Camera.h classes/Model.cpp classes/Model.h classes/Mesh.cpp classes/Mesh.h classes/ChessFigure.cpp classes/ChessFigure.h classes/PointLight.cpp classes/PointLight.h classes/DirectionalLight.cpp classes/DirectionalLight.h classes/SpotLight.cpp classes/SpotLight.h classes/Material.cpp classes/Material.h)

target_link_libraries(rg_3d_sah glad glfw OpenGL::GL pthread ${ASSIMP_LIBRARIES} X11 Xrandr Xi dl stb)