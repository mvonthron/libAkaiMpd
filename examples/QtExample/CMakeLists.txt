find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
 
qt4_wrap_ui(UISrcs mainwindow.ui)
qt4_wrap_cpp(MOCSrcs mainwindow.h inputthread.h)
 
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${libAkaiMpd_SOURCE_DIR}/src/linux)
elseif(WIN32)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${libAkaiMpd_SOURCE_DIR}/src/win32)
endif()

set(CMAKE_CXX_FLAGS    "-std=c++11 ${CMAKE_CXX_LINK_FLAGS}")

add_executable(QtExample main.cpp mainwindow.cpp inputthread.cpp ${MOCSrcs} ${UISrcs})
target_link_libraries(QtExample ${QT_LIBRARIES} akaimpd)
