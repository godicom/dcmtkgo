project(dcmtkgo)
cmake_minimum_required(VERSION 2.8)
set(SRC_LIST
export.cpp
export.h
)
add_library(${PROJECT_NAME} STATIC ${SRC_LIST})

