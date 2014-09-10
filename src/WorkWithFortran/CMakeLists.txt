cmake_minimum_required (VERSION 2.8)

set (CMAKE_CXX_FLAGS "-Wno-c++11-extensions")
set (CMAKE_Fortran_FLAGS "-fno-underscoring")

# We must enable Fortran language, or we will get errors.
enable_language (Fortran)

add_executable (workwithfortran_exam01.exe
    workwithfortran_exam01_cpp.cpp
    workwithfortran_exam01_fortran.f90
)
