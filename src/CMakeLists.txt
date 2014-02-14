# program version
set(libAkaiMpd_VERSION_MAJOR 0)
set(libAkaiMpd_VERSION_MINOR 1)

# options
set(CMAKE_BUILD_TYPE    None)
#~ set(CMAKE_CXX_FLAGS    "-std=c++11 -Wno-c++11-compat​​​​​​​​​​​​​​​​​​​ ${CMAKE_CXX_LINK_FLAGS}")

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message("Linux")
    subdirs(linux)
elseif(WIN32)
    message("Win32")
    subdirs(win32)
else()
    message("Nope")
endif()

