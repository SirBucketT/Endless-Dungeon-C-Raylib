# Minimum required version of CMake
cmake_minimum_required(VERSION 3.16)

# Project name and language
project(Endless_Dungeon_C_Raylib C)

# Set C standard to C99
set(CMAKE_C_STANDARD 99)

include(FetchContent)

# Function to include dependencies via FetchContent
function(include_dependency libName gitURL gitTag)
    FetchContent_Declare(${libName}
            GIT_REPOSITORY ${gitURL}
            GIT_TAG        ${gitTag}
            GIT_SHALLOW    TRUE
            GIT_PROGRESS   TRUE
    )
    FetchContent_MakeAvailable(${libName})
endfunction()

# Add Raylib dependency
find_package(raylib QUIET)
if (NOT raylib_FOUND)
    message(STATUS "Getting Raylib from Github")

    # Avoid unnecessary builds
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

    include_dependency(raylib https://github.com/raysan5/raylib.git 4.5.0)
else()
    message(STATUS "Using local Raylib")
endif()

# Add executable
add_executable(Endless_Dungeon_C_Raylib main.c UI.c header.h ScreenRender.c)

# Include Raylib headers
target_include_directories(Endless_Dungeon_C_Raylib PRIVATE ${raylib_SOURCE_DIR}/src)

# Link Raylib library
target_link_libraries(Endless_Dungeon_C_Raylib PRIVATE raylib)

# Ensure that custom headers are included in the target
target_compile_definitions(Endless_Dungeon_C_Raylib PRIVATE SCREEN_WIDTH=1800 SCREEN_HEIGHT=900)
