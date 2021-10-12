cmake_minimum_required(VERSION 3.2)
project(rotator C CXX)

find_package (Threads)
set(SOURCE_FILES
	rotator.h
	rotator.cpp
)

add_library(rotator SHARED STATIC ${SOURCE_FILES})
target_link_libraries(rotator TCPclient Threads::Threads)

install(TARGETS rotator DESTINATION ${INSTALL_LIB_DIR})
install(FILES rotator.h DESTINATION ${INSTALL_INCLUDE_DIR})
