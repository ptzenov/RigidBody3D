cmake_minimum_required(VERSION 3.0) 
project(opengltraining)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "--std=c++11")
set(CMAKE_CXX "g++")

set(CMAKE_BUILD_TYPE "Debug")
set(OIS_LIBRARY_DIRS "/usr/lib/x86_64-linux-gnu")


set(OPENGL false)

#Bring the headers, such as Student.h into the project
include_directories(
	"include"
	)

link_directories(
	"lib"
	)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif(OPENMP_FOUND)

if(OPENGL)
	message(STATUS "openGL build")
	find_package(OpenGL)
	find_package (GLUT)
	find_package (GLFW)
	find_package (GLEW)
else(OPENGL)
	message(STATUS "OGRE build")
	find_package(OGRE 1.10 REQUIRED)
	include_directories(
		${OGRE_INCLUDE_DIRS} 
		)
	link_directories(
		${CMAKE_LIBRARY_DIRS}
		${OGRE_LIBRARY_DIRS}
		${OIS_LIBRARY_DIRS}
		)
	file(COPY ${OGRE_CONFIG_DIR}/plugins.cfg ${OGRE_CONFIG_DIR}/resources.cfg 
	DESTINATION ${CMAKE_BINARY_DIR})
endif(OPENGL)

set(PRJNAME "RigidBody3D")
#set(SOURCE "src/main.cpp" "src/renderer.cpp" "src/inputs.cpp")
file(GLOB SOURCE "src/*.cpp")

add_executable(${PRJNAME} ${SOURCE})
target_link_libraries(${PRJNAME} ${OGRE_LIBRARIES} "OIS")

