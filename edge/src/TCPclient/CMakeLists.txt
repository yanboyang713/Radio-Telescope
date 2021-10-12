cmake_minimum_required(VERSION 3.2)
project(division C CXX)

set(SOURCE_FILES
	TCPclient.h
	TCPclient.cpp
)

add_library(TCPclient SHARED STATIC ${SOURCE_FILES})

install(TARGETS TCPclient DESTINATION ${INSTALL_LIB_DIR})
install(FILES TCPclient.h DESTINATION ${INSTALL_INCLUDE_DIR})
