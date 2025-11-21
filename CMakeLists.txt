cmake_minimum_required(VERSION 3.10)
project(QingEmulator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(QingEmulator
    main.cpp
    Game.cpp
    Province.cpp
    General.cpp
)

target_include_directories(QingEmulator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
