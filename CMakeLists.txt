cmake_minimum_required(VERSION 3.17)
project(rg_3d_sah)

set(CMAKE_CXX_STANDARD 14)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(libs/glad/)
add_subdirectory(libs/stb/)

add_executable(rg_3d_sah src/main.cpp classes/Shader.cpp classes/Shader.h classes/Texture2D.cpp classes/Texture2D.h classes/error.h classes/Camera.cpp classes/Camera.h)

target_link_libraries(rg_3d_sah glad glfw OpenGL::GL pthread X11 Xrandr Xi dl stb)