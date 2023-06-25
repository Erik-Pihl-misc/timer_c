cmake_minimum_required(VERSION 3.20)
project(timer) 
include_directories(../inc) 
add_executable(run_timer ../src/main.c ../src/timer.c)