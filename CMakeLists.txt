cmake_minimum_required(VERSION 3.10)
Project(mp4_to_ascii_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use Clang (LLVM) as the compiler
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

#Find OpenCV package
find_package(OpenCV REQUIRED)

#Include directoreis from OpenCV
include_directories(${OpenCV_INCLUDE_DIRS})

#Create executable
add_executable(mp4_to_ascii_cpp main.cpp)

#Link OpenCV libraries
target_link_libraries(mp4_to_ascii_cpp ${OpenCV_LIBS} opencv_videoio)