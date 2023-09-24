cmake_minimum_required(VERSION 3.5)

set(TARGET "calculator")

project(${TARGET} LANGUAGES CXX)

add_executable(
    ${TARGET}
    calculator.cpp
    token.cpp
    variable.cpp
)

install(TARGETS ${TARGET})
