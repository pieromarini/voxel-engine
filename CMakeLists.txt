cmake_minimum_required(VERSION 3.1)

project(voxel_engine)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g -Wall -grecord-gcc-switches -O2 -pipe -Werror=format-security -Werror=implicit-function-declaration -D_FORTIFY_SOURCE=2 -D_GLIBCXX_ASSERTIONS -fstack-clash-protection")

set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

# File Gathering
file(GLOB_RECURSE HDRS
	${SRC_DIR}/*.h
	${SRC_DIR}/*.hpp
)
file(GLOB_RECURSE SRCS
	${SRC_DIR}/*.cpp
	${SRC_DIR}/*.c
)

add_executable(${PROJECT_NAME} ${HDRS} ${SRCS})

# Use Modern OpenGL
set(OpenGL_GL_PREFERENCE "GLVND")

include(FindPkgConfig)


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${LIB_DIR}/glfw)

find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
	message(FATAL_ERROR "OpenGL not found!")
endif(NOT OPENGL_FOUND)

find_package(GLEW REQUIRED)
if(NOT GLEW_FOUND)
	message(FATAL_ERROR "GLEW not found!")
endif(NOT GLEW_FOUND)

find_package(ASSIMP REQUIRED)
if(NOT ASSIMP_FOUND)
	message(FATAL_ERROR "ASSIMP not found!")
endif(NOT ASSIMP_FOUND)

find_package(SOIL REQUIRED)
if(NOT SOIL_FOUND)
	message(FATAL_ERROR "SOIL not found!")
endif(NOT SOIL_FOUND)


# Define the include DIRs
include_directories( ${PROJECT_NAME}
	${engine_SOURCE_DIR}/src
	${OPENGL_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIRS}
	${ASSIMP_INCLUDE_DIRS}
	${SOIL_INCLUDE_DIRS}
	${GLFW_INCLUDE_DIRS}
)

# Define the link libraries
target_link_libraries( ${PROJECT_NAME}
	glfw
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	${ASSIMP_LIBRARIES}
	${SOIL_LIBRARIES}
)

# So we can use resources/ folder from build dir.
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${voxel_engine_SOURCE_DIR}/resources ${voxel_engine_BINARY_DIR}/resources RESULT_VARIABLE exitcode)
