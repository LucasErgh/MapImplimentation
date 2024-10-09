cmake_minimum_required(VERSION 3.30.0 FATAL_ERROR)

set(Sources
    "MyMap.cpp"
)

set(Dirs
    "../include")

add_library(src PUBLIC ${Dirs})

target_include_directories(src PUBLIC ${Dirs})