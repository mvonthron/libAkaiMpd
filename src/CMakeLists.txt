# program version
set(libAkaiMpd_VERSION_MAJOR 0)
set(libAkaiMpd_VERSION_MINOR 1)

# options
set(CMAKE_BUILD_TYPE    None)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    subdirs(linux)
elseif(WIN32)
    subdirs(win32)
else()
    message("Nope")
endif()

