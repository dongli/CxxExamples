cmake_minimum_required (VERSION 2.8)

find_package (Boost)

include_directories (${Boost_INCLUDE_DIR})

set (sources data_pointer_exam01.cpp)

foreach (source ${sources})
    get_filename_component (exam ${source} NAME_WE)
	add_executable (${exam}.exe ${source})
endforeach ()
