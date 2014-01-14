#!/bin/bash

echo "---------------------------------------------------------"
echo "[Notice]: Call CMake to prepare or update Makefile."
cmake .
echo "---------------------------------------------------------"
echo "[Notice]: Build examples ..."
make
echo "---------------------------------------------------------"
echo "[Notice]: Run examples ..."
for dir in $(ls src); do
	echo "========================================================="
	echo "[Notice]: Enter ./src/${dir}."
	for exe in $(ls ./src/${dir}/*.exe); do
		echo "[Notice]: Run $(basename ${exe})"
		${exe}
	done
done