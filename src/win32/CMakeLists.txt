include_directories(${libAkaiMpd_SOURCE_DIR}/src)
add_library(akaimpd SHARED devicemanager.cpp device.cpp)
target_link_libraries(akaimpd winmm)
