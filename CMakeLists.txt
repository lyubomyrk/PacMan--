cmake_minimum_required(VERSION 3.22)

project("PacMan++" LANGUAGES CXX)
set(EXECUTABLE "PacMan++")
add_executable(${EXECUTABLE})

# source files
file(GLOB SOURCES "Source/*.cpp")
file(GLOB_RECURSE HEADERS "Source/Include/*.hpp")
target_sources(${EXECUTABLE} PRIVATE ${SOURCES} ${HEADERS})

# header files
target_include_directories(${EXECUTABLE} PRIVATE Source/Include)

set_property(TARGET ${EXECUTABLE} PROPERTY CXX_STANDARD 17)

if (MINGW)
    target_include_directories(${EXECUTABLE} PRIVATE ${CMAKE_SOURCE_DIR}/Deps/raylib-mingw64/include/)
    target_link_libraries(${EXECUTABLE} PRIVATE ${CMAKE_SOURCE_DIR}/Deps/raylib-mingw64/lib/libraylib.a)
    target_link_libraries(${EXECUTABLE} PRIVATE opengl32)
    target_link_libraries(${EXECUTABLE} PRIVATE gdi32)
    target_link_libraries(${EXECUTABLE} PRIVATE winmm)
endif() 

if (UNIX)
  target_include_directories(${EXECUTABLE} PRIVATE ${CMAKE_SOURCE_DIR}/Deps/raylib-linux/include/)
  target_link_libraries(${EXECUTABLE} PRIVATE ${CMAKE_SOURCE_DIR}/Deps/raylib-linux/lib/libraylib.a)
endif()

