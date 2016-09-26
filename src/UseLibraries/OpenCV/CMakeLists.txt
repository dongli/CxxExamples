cmake_minimum_required (VERSION 2.8)

find_package (OpenCV REQUIRED)
include_directories (${OpenCV_INCLUDE_DIRS})

set (sources opencv_exam01.cpp opencv_exam02.cpp)

foreach (source ${sources})
  get_filename_component (exam ${source} NAME_WE)
  add_executable (${exam}.exe ${source})
  target_link_libraries (${exam}.exe ${OpenCV_LIBS})
endforeach ()
