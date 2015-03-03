project(dcmtkgo)
cmake_minimum_required(VERSION 2.8)

add_definitions(-DHAVE_CONFIG_H)
set(SRC_LIST
export.cpp
export.h
)

add_definitions(-std=c++11)

find_package(DCMTK)

include_directories(${DCMTK_INCLUDE_DIRS})

add_library(${PROJECT_NAME} STATIC ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${DCMTK_LIBRARIES})

