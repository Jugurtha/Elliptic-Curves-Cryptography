cmake_minimum_required(VERSION 3.7...3.27)

set( CMAKE_CXX_COMPILER "C:/TDM-GCC-64/bin/g++.exe" )
set( CMAKE_C_COMPILER "C:/TDM-GCC-64/bin/gcc.exe" )
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(ECDH VERSION 1.0
                  DESCRIPTION "ECDH"
                  LANGUAGES CXX)

add_executable(ECDH main.cpp Integer.h Point.h EllipticCurve.h)
