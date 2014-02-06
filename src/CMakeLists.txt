# project name
project(libAkaiMpd)

# CMake version
cmake_minimum_required(VERSION 2.6)

# program
set(_SOURCES device.cpp devicemanager.cpp main.cpp)
set(_HEADERS device.h devicemanager.h utils.h)
add_executable(akaimpd ${_SOURCES} ${_HEADERS})

target_link_libraries (akaimpd asound) 

# program version
set(libAkaiMpd_VERSION_MAJOR 0)
set(libAkaiMpd_VERSION_MINOR 1)

# options
set(CMAKE_BUILD_TYPE    None)
set(CMAKE_CXX_FLAGS    "-std=c++11 -Wno-c++11-compat​​​​​​​​​​​​​​​​​​​ ${CMAKE_CXX_LINK_FLAGS}")
set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_FLAGS} -lasound ")

if(LINUX)
    message("Unix")
elseif(WIN32)
    message("Win32")
elseif(APPLE)
    message("Apple")
else()
    message("Another")
endif()
