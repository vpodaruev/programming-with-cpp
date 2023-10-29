cmake_minimum_required(VERSION 3.20)

set(TARGET "calculator")

set(SOURCES
    calculator.cpp
)

project(${TARGET} CXX)

add_executable(${TARGET} ${SOURCES})

install(TARGETS ${TARGET})
