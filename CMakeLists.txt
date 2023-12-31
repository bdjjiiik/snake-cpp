cmake_minimum_required(VERSION 3.26)
project(snake)

set(CMAKE_CXX_STANDARD 20)

# raylib
find_package(raylib QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git
            GIT_TAG 4.5.0
    )
    FetchContent_MakeAvailable(raylib)
endif()

# raylib-cpp
find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib_cpp
            GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
            GIT_TAG v4.5.1
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif()

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

add_executable(${PROJECT_NAME} main.cpp
        Game.cpp
        Game.h
        Utils.h
        src/objects/Snake.h
        src/objects/Fruit.h
        Render.cpp
        Render.h
        Collision.cpp
        Collision.h
        src/objects/GameObject.h
        Vector.h
        Color.h
        GraphicRender.h)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib raylib_cpp)
