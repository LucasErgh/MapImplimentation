cmake_minimum_required(VERSION 3.30.0 FATAL_ERROR)

project(MapImplimentation LANGUAGES CXX) # create project

add_executable(Map src/Map.cpp) # create executable target, compile and link Map.cpp

# Add the include directory so that Map.cpp can find MyMap.h
target_include_directories(Map PUBLIC include)