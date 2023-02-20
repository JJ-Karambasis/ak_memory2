@echo off

clang -std=c89 -O0 -g -Wextra -fdiagnostics-absolute-paths ak_memory_tests.c -o tests.exe