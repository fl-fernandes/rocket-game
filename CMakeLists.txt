cmake_minimum_required(VERSION 3.20)
project(rocket-game
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)

# Fetch source of SDL2
include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(sdl2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG release-2.0.22
)

FetchContent_GetProperties(sdl2)
if(NOT sdl2_POPULATED)
FetchContent_Populate(sdl2)
    add_subdirectory(${sdl2_SOURCE_DIR} ${sdl2_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# for SDL2 header files
include_directories(${sdl2_SOURCE_DIR}/include)

#Game engine
add_library(EngineLib game_lib.cpp)

#Main game
add_executable(rocket-game rocket_game.cpp)
target_link_libraries(rocket-game PRIVATE EngineLib SDL2::SDL2)