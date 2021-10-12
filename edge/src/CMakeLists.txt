cmake_minimum_required(VERSION 3.2)
project(radioTelescope)
find_package (Threads)

add_subdirectory(TCPclient)
add_subdirectory(httpPOSTjson)
add_subdirectory(rotatorManagement)
set(SOURCE_FILES main.cpp main.h)

add_executable(radioTelescope ${SOURCE_FILES})

target_link_libraries(radioTelescope postJSON rotator Threads::Threads)

install(TARGETS radioTelescope DESTINATION ${INSTALL_BIN_DIR})

