cmake_minimum_required(VERSION 3.13)

project(AIplay VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Nạp trực tiếp file cấu hình Geode SDK từ môi trường Runner
if(DEFINED ENV{GEODE_SDK})
    include("$ENV{GEODE_SDK}/share/Geode/cmake/GeodeFile.cmake")
else()
    find_package(Geode REQUIRED)
endif()

add_library(${PROJECT_NAME} SHARED
    src/main.cpp
)

setup_geode_mod(${PROJECT_NAME})
