# CMakeList.txt : CMake project for Pacman, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.22)

project("PacMan++" LANGUAGES CXX)
set(EXECUTABLE "PacMan++")

# source files
file(GLOB SOURCES "Source/*.cpp")
file(GLOB HEADERS "Source/Include/*.hpp")
add_executable (${EXECUTABLE} ${SOURCES} ${HEADERS})

# header files
target_include_directories(${EXECUTABLE} PRIVATE Source/Include)

set_property(TARGET ${EXECUTABLE} PROPERTY CXX_STANDARD 20)

if (UNIX)
  target_include_directories(${EXECUTABLE} PRIVATE Deps/raylib-linux/include/)
  target_link_libraries(${EXECUTABLE} PRIVATE ${CMAKE_SOURCE_DIR}/Deps/raylib-linux/lib/libraylib.a)
endif()