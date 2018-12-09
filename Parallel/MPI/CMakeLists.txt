cmake_minimum_required(VERSION 3.13)
project(MPI)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_C_COMPILER /opt/usr/local/bin/mpicc)
#set(CMAKE_CXX_COMPILER /opt/usr/local/bin/mpic++)


add_executable(MPI main.cpp)
