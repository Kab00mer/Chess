cmake_minimum_required(VERSION 3.28)
project(Chess)

set(CMAKE_CXX_STANDARD 			 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS 		OFF)

add_executable(${PROJECT_NAME} *.cpp)

target_link_libraries(${PROJECT_NAME} SDL3)

add_subdirectory(libs)
