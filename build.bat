@echo off

clang++ -std=c++11 -O0 -g -Wextra -Wno-unused-parameter -fdiagnostics-absolute-paths ak_memory_tests.cpp -o tests.exe