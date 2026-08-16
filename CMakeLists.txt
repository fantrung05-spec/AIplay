cmake_minimum_required(VERSION 3.13)

# Khai bao duong dan SDK tu Geode CLI cho CMake
if(DEFINED ENV{GEODE_SDK})
    set(Geode_DIR "$ENV{GEODE_SDK}")
    list(APPEND CMAKE_PREFIX_PATH "$ENV{GEODE_SDK}")
endif()

project(AIplay VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Geode REQUIRED)

add_library(${PROJECT_NAME} SHARED
    src/main.cpp
)

setup_geode_mod(${PROJECT_NAME})
