cmake_minimum_required(VERSION 3.20)

set(TARGET "logic_elements")

project(${TARGET} LANGUAGES CXX)

add_executable(
    ${TARGET}
    main.cpp
    logic.cpp
    logic.h
)

install(TARGETS ${TARGET})
