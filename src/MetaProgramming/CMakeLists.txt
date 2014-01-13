cmake_minimum_required (VERSION 2.8)

set (CMAKE_CXX_FLAGS "-Wno-c++11-extensions")

set (sources metaprogramming_exam01.cpp)

foreach (source ${sources})
    get_filename_component (exam ${source} NAME_WE)
	add_executable (${exam}.exe ${source})
endforeach ()
