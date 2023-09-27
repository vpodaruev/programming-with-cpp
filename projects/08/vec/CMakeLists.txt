cmake_minimum_required(VERSION 3.20)

set(TARGET "vec")

project(${TARGET} LANGUAGES CXX)

add_executable(
    ${TARGET}
    main.cpp
    ${LIB_DIR}/vec/vec2d.h
    ${LIB_DIR}/vec/vec2d.cpp
)

install(TARGETS ${TARGET})
