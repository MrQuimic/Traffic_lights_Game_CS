cmake_minimum_required(VERSION 3.19)
project(Traffic_lights_Game_CS C)

set(CMAKE_C_STANDARD 99)

add_executable(Traffic_lights_Game_CS main.c moves.h moves.c utils.h utils.c gdata.c gdata.h)