find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
 
qt4_wrap_ui(UISrcs mainwindow.ui)
qt4_wrap_cpp(MOCSrcs mainwindow.h inputthread.h)
 
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ../../src/linux)

add_executable(QtExample main.cpp mainwindow.cpp inputthread.cpp ${MOCSrcs} ${UISrcs})
target_link_libraries(QtExample ${QT_LIBRARIES} akaimpd)
