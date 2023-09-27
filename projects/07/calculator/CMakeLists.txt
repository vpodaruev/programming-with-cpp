cmake_minimum_required(VERSION 3.20)

set(TARGET "calculator")

project(${TARGET} LANGUAGES CXX)

add_executable(
    ${TARGET}
    calculator.cpp
)

install(TARGETS ${TARGET})
