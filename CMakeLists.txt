cmake_minimum_required(VERSION 3.13)

project(AIplay VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tự động nạp Geode CLI / SDK từ môi trường của GitHub Action
if (DEFINED ENV{GEODE_SDK})
    include("$ENV{GEODE_SDK}/share/Geode/cmake/GeodeFile.cmake")
else()
    include(FetchContent)
    FetchContent_Declare(
        Geode
        GIT_REPOSITORY https://github.com/geode-sdk/geode.git
        GIT_TAG main
    )
    FetchContent_MakeAvailable(Geode)
endif()

add_library(${PROJECT_NAME} SHARED
    src/main.cpp
)

setup_geode_mod(${PROJECT_NAME})
