# CMakeList.txt : CMake project for Pacman, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.22)

project("PacMan++" LANGUAGES CXX)
set(EXECUTABLE "PacMan++")

# source files
file(GLOB SOURCES "Source/*.cpp")
add_executable (${EXECUTABLE} ${SOURCES})

# header files
include_directories("Source/Include/")

target_compile_features(${EXECUTABLE} PUBLIC cxx_std_20)

# if (UNIX)
#   target_include_directories(${EXECUTABLE} PRIVATE Deps/raylib-linux/include)
#   target_link_libraries(${EXECUTABLE} PRIVATE ${CMAKE_SOURCE_DIR}/Deps/raylib-linux/lib/libraylib.a)
# endif()