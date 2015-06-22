cmake_minimum_required (VERSION 2.8)

find_package (Boost 1.55.0 REQUIRED
    COMPONENTS date_time locale
)

set (sources
    datetime_exam01.cpp
)

foreach (source ${sources})
    get_filename_component (exam ${source} NAME_WE)
	add_executable (${exam}.exe ${source})
    target_link_libraries (${exam}.exe ${Boost_LIBRARIES})
endforeach ()
