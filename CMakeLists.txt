cmake_minimum_required(VERSION 2.8)
find_package(SWIG REQUIRED)
mark_as_advanced(SWIG_DIR SWIG_EXECUTABLE SWIG_VERSION)
include(${SWIG_USE_FILE})
add_definitions( -DHAVE_CONFIG_H)
add_definitions( -D__x86_64__)


find_package(DCMTK REQUIRED)

if (APPLE)
include_directories(/usr/local/include/)
else(LINUX)
include_directories(/usr/include/)
#include_directories(/usr/include/linux/)
#include_directories(/usr/lib/gcc/x86_64-linux-gnu/4.7.2)
#include_directories(/usr/include/c++/4.7/)
#include_directories(/usr/include/c++/4.7/tr1/)
#include_directories(/usr/include/c++/4.7/x86_64-linux-gnu)
#include_directories(/usr/include/x86_64-linux-gnu/)
endif()



INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_SWIG_FLAGS -intgosize 64 -c++)

SET_SOURCE_FILES_PROPERTIES(dcmtkgo.i PROPERTIES CPLUSPLUS ON)
#SET_SOURCE_FILES_PROPERTIES(dcmtkgo.i PROPERTIES SWIG_FLAGS "-includeall")


SWIG_ADD_MODULE(dcmtkgo go dcmtkgo.i)
SWIG_LINK_LIBRARIES(dcmtkgo ${DCMTK_LIBRARIES})