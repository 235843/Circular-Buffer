cmake_minimum_required(VERSION 3.17)
project(BUFOR C)

set(CMAKE_C_STANDARD 11)

add_executable(BUFOR main.c circular_buffer.c circular_buffer.h)