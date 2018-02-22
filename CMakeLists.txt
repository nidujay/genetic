cmake_minimum_required(VERSION 3.0)
project(genetic)

macro(use_cxx11)
	if (CMAKE_VERSION VERSION_LESS "3.1")
		if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
			set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
		endif ()
	else ()
		set (CMAKE_CXX_STANDARD 11)
	endif ()
endmacro(use_cxx11)

set(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
use_cxx11()

set (CMAKE_CXX_STANDARD 11)

find_package(GALIB REQUIRED)

add_executable(genetic
	main.cpp
	fitness.cpp
	grade.cpp
	histogram.cpp
)

target_link_libraries(genetic ${GALIB_LIBRARIES})

add_library(school-grade
	fitness.cpp
)

target_include_directories(school-grade
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(test)
