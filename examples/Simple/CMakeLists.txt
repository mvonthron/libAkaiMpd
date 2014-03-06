include_directories(${libAkaiMpd_SOURCE_DIR}/src)


if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    include_directories(${libAkaiMpd_SOURCE_DIR}/src/linux)
elseif(WIN32)
    include_directories(${libAkaiMpd_SOURCE_DIR}/src/win32)
endif()


set(CMAKE_CXX_FLAGS    "-std=c++11 ${CMAKE_CXX_LINK_FLAGS}")

add_executable(simple simple.cpp)
target_link_libraries(simple akaimpd)
