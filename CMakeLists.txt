project(libAkaiMpd)
cmake_minimum_required(VERSION 2.6)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${libAkaiMpd_SOURCE_DIR}/bin/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${libAkaiMpd_SOURCE_DIR}/bin/")

subdirs(src examples)
