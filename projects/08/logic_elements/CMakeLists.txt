cmake_minimum_required(VERSION 3.20)

set(TARGET "logic_elements")

set(HEADERS
    logic.h
)
set(SOURCES
    main.cpp
    logic.cpp
)

project(${TARGET} CXX)

add_executable(${TARGET} ${HEADERS} ${SOURCES})

install(TARGETS ${TARGET})
