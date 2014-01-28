#!/bin/bash

build_root="./build.make"
if [[ ! -d "$build_root" ]]; then
    mkdir "$build_root"
    echo "[Notice]: Build directory $build_root is created."
fi
cd $build_root
echo "---------------------------------------------------------"
echo "[Notice]: Call CMake to prepare or update Makefile."
cmake ..
echo "---------------------------------------------------------"
echo "[Notice]: Build examples ..."
make
echo "---------------------------------------------------------"
echo "[Notice]: Run examples ..."
for dir in $(ls src); do
	echo "========================================================="
	echo "[Notice]: Enter ./src/${dir}."
	for exe in $(find ./src/${dir} -name '*.exe'); do
	    echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
		echo "[Notice]: Run $(basename ${exe})"
		${exe}
	done
done
