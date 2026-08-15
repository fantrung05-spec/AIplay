cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(AIplay VERSION 1.0.0 LANGUAGES CXX)

add_library(${PROJECT_NAME} SHARED
    src/main.cpp
)

include(FetchContent)
FetchContent_Declare(
    Geode
    GIT_REPOSITORY https://github.com/geode-sdk/geode
    GIT_TAG main
)
FetchContent_MakeAvailable(Geode)

setup_geode_mod(${PROJECT_NAME})
