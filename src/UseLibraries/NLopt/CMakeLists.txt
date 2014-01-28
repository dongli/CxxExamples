cmake_minimum_required (VERSION 2.8)

# ------------------------------------------------------------------------------
# external libraries
if (NOT DEFINED ENV{NLOPT_ROOT})
    message (FATAL_ERROR
            "CMake couldn't find library NLopt! "
            "If it have been installed and you know where it is, "
            "set NLOPT_ROOT (e.g. in .bashrc) to it."
    )
else ()
    set (NLOPT_INCLUDE_DIR "$ENV{NLOPT_ROOT}/include")
    set (NLOPT_LIBRARY_DIR "$ENV{NLOPT_ROOT}/lib")
endif ()

find_package (Armadillo)
if (NOT ARMADILLO_FOUND)
    if (DEFINED ENV{ARMADILLO_ROOT})
        message ("@@ Use user provided library Armadillo!")
        message ("@@ ARMADILLO_ROOT = $ENV{ARMADILLO_ROOT}")
        find_package (Armadillo HINTS $ENV{ARMADILLO_ROOT})
    else ()
        message (FATAL_ERROR
            "CMake couldn't find library Armadillo! "
            "If it have been installed and you know where it is, "
            "set ARMADILLO_ROOT (e.g. in .bashrc) to it."
        )
    endif ()
endif ()

include_directories (
    ${NLOPT_INCLUDE_DIR}
    ${ARMADILLO_INCLUDE_DIRS}
)
link_directories (
    ${NLOPT_LIBRARY_DIR}
)


# ------------------------------------------------------------------------------
set (sources nlopt_exam01.cpp)

foreach (source ${sources})
    get_filename_component (tmp ${source} NAME_WE)
    set (exam "${tmp}.exe")
	add_executable (${exam} ${source})
	target_link_libraries (${exam} ${ARMADILLO_LIBRARY} nlopt)
endforeach ()
