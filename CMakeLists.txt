cmake_minimum_required(VERSION 3.30.0 FATAL_ERROR)

project(MapImplimentation)

add_executable(Map src/Map.cpp)

add_library(MyMap src/MyMap.cpp)
target_include_directories(MyMap PUBLIC include)

target_link_libraries(Map MyMap)