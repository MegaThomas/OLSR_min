cmake_minimum_required(VERSION 3.6)
project(OLSR_min)

set(SOURCE_FILES main.c olsr_type.c olsr_type.h)
add_executable(OLSR_min ${SOURCE_FILES})