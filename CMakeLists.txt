cmake_minimum_required(VERSION 3.17)
project(Consolation C)

set(CMAKE_C_STANDARD 99)

add_library(Consolation consolation.h consolation.c file.h file.c font.h stb_image.h)
add_subdirectory(vendor/glfw)
target_link_libraries(Consolation PRIVATE glfw)
add_subdirectory(vendor/glew/build/cmake)
target_link_libraries(Consolation PRIVATE glew)

project(ConsolationTest C CXX)
add_executable(ConsolationTest main.c)
target_link_libraries(ConsolationTest Consolation)