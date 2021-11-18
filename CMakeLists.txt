cmake_minimum_required(VERSION 2.8)

project(Disk)

set(Disk_src Test.cpp main.cpp FileSystem.cpp)
set(Disk_hdr Header.h)

add_executable(${PROJECT_NAME} ${Disk_src} ${Disk_hdr})