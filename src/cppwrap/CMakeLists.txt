project(dcmtkgo)
cmake_minimum_required(VERSION 2.8)
set(SRC_LIST
export.cpp
export.h
)

if(APPLE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

add_library(${PROJECT_NAME} STATIC ${SRC_LIST})

