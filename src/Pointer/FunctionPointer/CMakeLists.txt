cmake_minimum_required (VERSION 2.8)

set (sources function_pointer_exam01.cpp)

foreach (source ${sources})
    get_filename_component (exam ${source} NAME_WE)
	add_executable (${exam}.exe ${source})
endforeach ()
