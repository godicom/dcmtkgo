project(dcmtkgo)
cmake_minimum_required(VERSION 2.8)
set(SRC_LIST
export.cpp
export.h
)


find_package(DCMTK)
if(APPLE)
include_directories(${DCMTK_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

add_library(${PROJECT_NAME} STATIC ${SRC_LIST})
message(${DCMTK_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${DCMTK_LIBRARIES})

