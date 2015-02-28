cmake_minimum_required(VERSION 2.8)
find_package(SWIG REQUIRED)
mark_as_advanced(SWIG_DIR SWIG_EXECUTABLE SWIG_VERSION)
include(${SWIG_USE_FILE})
add_definitions( -DHAVE_CONFIG_H)


find_package(DCMTK REQUIRED)

if (APPLE)
include_directories(/usr/local/include/)
else()
include_directories(/usr/include/)
endif()

#mark_as_advanced(SWIG_DIR SWIG_EXECUTABLE SWIG_VERSION)



INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_SWIG_FLAGS -intgosize 64)

SET_SOURCE_FILES_PROPERTIES(dcmtkgo.i PROPERTIES CPLUSPLUS ON)
#SET_SOURCE_FILES_PROPERTIES(dcmtkgo.i PROPERTIES SWIG_FLAGS "-includeall")

SWIG_ADD_MODULE(dcmtkgo go dcmtkgo.i)
SWIG_LINK_LIBRARIES(dcmtkgo ${DCMTK_LIBRARIES})