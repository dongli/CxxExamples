cmake_minimum_required (VERSION 2.8)

find_package (OpenMP)

if (OPENMP_FOUND)
    set (sources openmp_exam01.cpp openmp_exam02.cpp)

    foreach (source ${sources})
        get_filename_component (exam ${source} NAME_WE)
        add_executable (${exam}.exe ${source})
    endforeach ()
endif ()
