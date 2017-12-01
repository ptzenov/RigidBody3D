cmake_minimum_required(VERSION 3.0) 
project(opengltraining)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "--std=c++11")
set(CMAKE_CXX "g++")

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
	include_directories(${OGRE_INCLUDE_DIRS})
	link_directories(
		${CMAKE_LIBRARY_DIRS}
		${OGRE_LIBRARY_DIRS}
		)
	file(COPY ${OGRE_CONFIG_DIR}/plugins.cfg ${OGRE_CONFIG_DIR}/resources.cfg 
	DESTINATION ${CMAKE_BINARY_DIR})
endif(OPENGL)

set(PRJNAME "RigidBody3D")
set(SOURCE "src/main.cpp" "src/renderer.cpp")
add_executable(${PRJNAME} ${SOURCE})


if(OPENGL)
if (OPENGL_FOUND)
	include_directories(${OPENGL_INDLUCE_DIRS})
	target_link_libraries (${PRJNAME} ${OPENGL_LIBRARIES})
endif(OPENGL_FOUND)
if (GLUT_FOUND)
	include_directories(${GLUT_INCLUDE_DIRS})
	target_link_libraries (${PRJNAME} ${GLUT_LIBRARIES})
endif (GLUT_FOUND)
if (GLEW_FOUND)
	include_directories(${GLEW_INCLUDE_DIRS})
	target_link_libraries (${PRJNAME} ${GLEW_LIBRARIES})
endif (GLEW_FOUND)
else(OPENGL)
	include_directories(${OGRE_INCLUDE_DIRS})
	target_link_libraries (${PRJNAME} ${OGRE_LIBRARIES})
endif(OPENGL)

