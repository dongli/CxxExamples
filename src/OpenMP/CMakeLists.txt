cmake_minimum_required (VERSION 2.8)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

find_package (OpenMP)

if (OPENMP_FOUND)
    set (sources openmp_exam01.cpp openmp_exam02.cpp openmp_exam03.cpp)

    foreach (source ${sources})
        get_filename_component (exam ${source} NAME_WE)
        add_executable (${exam}.exe ${source})
    endforeach ()
endif ()
