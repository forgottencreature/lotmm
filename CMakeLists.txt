cmake_minimum_required(VERSION 3.5)
project(tile_sfml_game)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Camera.cpp Player.cpp Tile.cpp TileMap.cpp)

add_executable(tile_sfml_game ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(tile_sfml_game ${SFML_LIBRARIES})
endif()