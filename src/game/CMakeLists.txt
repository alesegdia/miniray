set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(BOX2D REQUIRED)
find_package(Freetype REQUIRED)

file( GLOB_RECURSE SRCs */*.cpp )
file( GLOB_RECURSE INCs */*.h )
file( GLOB_RECURSE GLRAYFW_SOURCES
	../../lib/glrayfw/glrayfw/*/*.cpp
	../../lib/glrayfw/glrayfw/*/*.h
	)

add_library(glrayfw ${GLRAYFW_SOURCES})
add_executable(miniray-game main.cpp ${SRCs})

target_link_libraries(miniray-game glrayfw)
include_directories(../../lib/cml/)
include_directories(../../lib/glrayfw/)

if(SDL2_FOUND)
	include_directories(${SDL2_INCLUDE_DIR})
	target_link_libraries(miniray-game ${SDL2_LIBRARY})
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

