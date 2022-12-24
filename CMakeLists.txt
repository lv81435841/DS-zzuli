cmake_minimum_required(VERSION 3.23)
project(clion)

set(CMAKE_CXX_STANDARD 11)
IF (WIN32)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fexec-charset=GBK")
ENDIF ()
add_executable(clion main.cpp)
