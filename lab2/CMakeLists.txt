cmake_minimum_required(VERSION 3.8)

project(2_4_)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(LibXML++ REQUIRED)
include_directories(${LibXML++_INCLUDE_DIRS})
set(LIBS ${LIBS} ${LibXML++_LIBRARIES})

configure_file(weather.xml weather.xml COPYONLY)

add_executable(2_4_ main.cpp)

target_link_libraries(2_4_ ${LIBS})