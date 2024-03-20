cmake_minimum_required(VERSION 2.6)
project(miniray)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(SDL2_DIR C:/Users/alejandro.segui/SDL2-2.30.1)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" "sdldep/cmake" ${CMAKE_MODULE_PATH})
list(APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

set(SDL2_LIBRARY "../sdldep/lib/x64/SDL2")
set(SDL2_INCLUDE_DIR "sdldep/include")

set(BOX2D_LIBRARY "../box2ddep/box2d")
set(BOX2D_INCLUDE_DIR "box2ddep/include")

set(FREETYPE_LIBRARY "../freetypedeps/freetype")
set(FREETYPE_INCLUDE_DIRS "freetypedep/include")


find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(BOX2D REQUIRED)
find_package(Freetype REQUIRED)

include_directories(lib/glrayfw/include)
file(GLOB_RECURSE SOURCES src/game/**.cpp src/game/**.h)
file( GLOB_RECURSE GLRAYFW_SOURCES
	lib/glrayfw/glrayfw/**/*.cpp
	lib/glrayfw/glrayfw/**/*.h
	)

add_library(glrayfw ${GLRAYFW_SOURCES})
add_executable(miniray-game src/game/main.cpp ${SOURCES})

target_link_libraries(miniray-game glrayfw)
include_directories(lib/cml/)
include_directories(lib/glrayfw/)

if(SDL2_FOUND)
	include_directories(${SDL2_INCLUDE_DIR})
	target_link_libraries(miniray-game ${SDL2_LIBRARY})
	target_link_libraries(miniray-game "../sdldep/lib/x64/SDL2main")
endif()

if(OPENGL_FOUND)
	target_link_libraries(miniray-game ${OPENGL_LIBRARIES})
endif()

if(BOX2D_FOUND)
	include_directories(${BOX2D_INCLUDE_DIR})
	target_link_libraries(miniray-game ${BOX2D_LIBRARIES})
endif()

if(FREETYPE_FOUND)
	include_directories(${FREETYPE_INCLUDE_DIRS})
	target_link_libraries(miniray-game ${FREETYPE_LIBRARIES})
endif()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin/debug64)
set(LIBRARY_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/lib/debug64)

