cmake_minimum_required(VERSION 3.13)

project(GnuplotWrapper VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

set(LIBS_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/libs)

set(RAPIDJSON_ROOT ${LIBS_ROOT}/rapidjson)

include_directories(${RAPIDJSON_ROOT}/include)

file(GLOB_RECURSE proj_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(GnuplotWrapper STATIC ${proj_sources})

install(TARGETS GnuplotWrapper
        DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
