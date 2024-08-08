@echo off

cmake -B build -G "MinGW Makefiles"
cmake --build build --target all -j8 2> error.txt

pause