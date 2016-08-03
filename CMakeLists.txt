cmake_minimum_required(VERSION 3.5)
# Project Specific stuff
set(SOURCE_FILES main.cpp Camera.cpp Player.cpp Tile.cpp TileMap.cpp src/MyInterface.hpp)
set(PROJECT_NAME tilemap)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
message("Building ${PROJECT_NAME}...")
project(${PROJECT_NAME})

# CMake Options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_VERBOSE_MAKEFILE ON) # Lets see what the fuck is going on
set(CMAKE_RULE_MESSAGES OFF) # We don't need to see that much
if (APPLE)
    message("Found Apple Machine!")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -stdlib=libc++")
    set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
    set(CMAKE_C_COMPILER "/usr/bin/clang")
endif (APPLE)

# SFML Stuff
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    message("Found SFML...")
    include_directories(${SFML_INCLUDE_DIR} ${SFML_INCLUDE_DIRS}) # Do I need dir and dirs?
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
else ()
    message(FATAL_ERROR "Could not locate SFML!")
endif (SFML_FOUND)

# SFGUI Stuff
find_package(SFGUI REQUIRED)
if (SFGUI_FOUND)
    message("Found SFGUI...")
    include_directories(${SFGUI_INCLUDE_DIR} ${SFGUI_INCLUDE_DIRS}) # Do I need dir and dirs?
    target_link_libraries(${PROJECT_NAME} -lsfgui)
else ()
    message(FATAL_ERROR "Could not locate SFGUI!")
endif (SFGUI_FOUND)
