cmake_minimum_required(VERSION 3.5)
# Project Specific stuff
file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS src/*.hpp)
set(SOURCE_FILES ${SOURCES} ${HEADERS})
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