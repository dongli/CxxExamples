cmake_minimum_required (VERSION 2.8)

# ------------------------------------------------------------------------------
# external libraries
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

find_package (LibXml2)

if (NOT DEFINED ENV{MLPACK_ROOT})
    message (FATAL_ERROR
            "CMake couldn't find library MLPACK! "
            "If it have been installed and you know where it is, "
            "set MLPACK_ROOT (e.g. in .bashrc) to it."
    )
else ()
    set (MLPACK_INCLUDE_DIR "$ENV{MLPACK_ROOT}/include")
    set (MLPACK_LIBRARY_DIR "$ENV{MLPACK_ROOT}/lib")
endif ()

include_directories (
    ${ARMADILLO_INCLUDE_DIRS}
    ${LIBXML2_INCLUDE_DIR}
    ${MLPACK_INCLUDE_DIR}
)
link_directories (
    ${MLPACK_LIBRARY_DIR}
)


# ------------------------------------------------------------------------------
set (sources mlpack_exam01.cpp mlpack_exam02.cpp mlpack_exam03.cpp)

foreach (source ${sources})
    get_filename_component (tmp ${source} NAME_WE)
    set (exam "${tmp}.exe")
	add_executable (${exam} ${source})
	target_link_libraries (${exam} armadillo mlpack)
endforeach ()