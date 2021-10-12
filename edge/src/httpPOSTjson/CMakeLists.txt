cmake_minimum_required(VERSION 3.9)
project(postJSON C CXX)

set(SOURCE_FILES
	postJSON.h
	postJSON.cpp
)
set(cpprestsdk_DIR /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}/cmake/)
find_package(cpprestsdk REQUIRED)
find_package(Boost 1.65.1 COMPONENTS system)

add_library(postJSON SHARED STATIC ${SOURCE_FILES})
target_link_libraries(postJSON PRIVATE cpprestsdk::cpprest ${Boost_LIBRARIES})

install(TARGETS postJSON DESTINATION ${INSTALL_LIB_DIR})
install(FILES postJSON.h DESTINATION ${INSTALL_INCLUDE_DIR})
