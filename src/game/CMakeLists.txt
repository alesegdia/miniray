set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(CML REQUIRED)
find_package(BOX2D REQUIRED)
find_package(Freetype REQUIRED)

file( GLOB_RECURSE SRCs */*.cpp )
file( GLOB_RECURSE INCs */*.h )
add_executable(test main.cpp ${SRCs})


if(SDL2_FOUND)
	include_directories(${SDL2_INCLUDE_DIR})
	target_link_libraries(test ${SDL2_LIBRARY})
endif()

if(OPENGL_FOUND)
	target_link_libraries(test ${OPENGL_LIBRARIES})
endif()

if(BOX2D_FOUND)
	include_directories(${BOX2D_INCLUDE_DIR})
	target_link_libraries(test ${BOX2D_LIBRARIES})
endif()

if(FREETYPE_FOUND)
	include_directories(${FREETYPE_INCLUDE_DIRS})
	target_link_libraries(test ${FREETYPE_LIBRARIES})
endif()

include_directories(${CML_HEADER_PATH})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY} )

