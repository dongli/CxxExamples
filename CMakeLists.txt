cmake_minimum_required (VERSION 2.8)

project (cxx_examples CXX)

list (APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}")

add_subdirectory ("${PROJECT_SOURCE_DIR}/src/Pointer/DataPointer")
add_subdirectory ("${PROJECT_SOURCE_DIR}/src/Pointer/FunctionPointer")
add_subdirectory ("${PROJECT_SOURCE_DIR}/src/MetaProgramming")
add_subdirectory ("${PROJECT_SOURCE_DIR}/src/Hash")
add_subdirectory ("${PROJECT_SOURCE_DIR}/src/Container")
add_subdirectory ("${PROJECT_SOURCE_DIR}/src/RandomNumber")
add_subdirectory ("${PROJECT_SOURCE_DIR}/src/Polymorphism")
add_subdirectory ("${PROJECT_SOURCE_DIR}/src/OpenMP")
add_subdirectory ("${PROJECT_SOURCE_DIR}/src/UseLibraries/MLPACK")
# add_subdirectory ("${PROJECT_SOURCE_DIR}/src/UseLibraries/NLopt")
add_subdirectory ("${PROJECT_SOURCE_DIR}/src/C++11")
add_subdirectory ("${PROJECT_SOURCE_DIR}/src/WorkWithFortran")
