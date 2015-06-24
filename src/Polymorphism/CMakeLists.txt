cmake_minimum_required (VERSION 2.8)

set (CMAKE_CXX_FLAGS "-std=c++11")

find_package (Boost 1.55.0 REQUIRED)

set (sources
    polymorphism_exam01.cpp
    polymorphism_exam02.cpp
)

foreach (source ${sources})
    get_filename_component (exam ${source} NAME_WE)
	add_executable (${exam}.exe ${source})
endforeach ()
