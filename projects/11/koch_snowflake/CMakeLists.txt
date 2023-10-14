cmake_minimum_required(VERSION 3.20)

set(TARGET "snowflake")

project(${TARGET} LANGUAGES CXX)

add_executable(
    ${TARGET}
    main.cpp
    ${LIB_DIR}/vec/vec2d.h
    ${LIB_DIR}/vec/vec2d.cpp
    ${LIB_DIR}/poly/poly.h
    ${LIB_DIR}/poly/poly.cpp
    ${LIB_DIR}/Graph_lib/Graph.cpp
    ${LIB_DIR}/Graph_lib/GUI.cpp
    ${LIB_DIR}/Graph_lib/Window.cpp
)

install(TARGETS ${TARGET})

set(FLTK_SKIP_FLUID True)
set(OpenGL_GL_PREFERENCE "GLVND")

find_package(FLTK REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(
    SYSTEM
    ${FLTK_INCLUDE_DIR}
)

link_directories(
    ${FLTK_INCLUDE_DIR}/../lib
)

target_link_libraries(
    ${TARGET}
    ${FLTK_LIBRARIES}
    ${OPENGL_LIBRARIES}
)

if(WIN32)
target_link_libraries(
    ${TARGET}
    fltk_jpeg
    fltk_png
    fltk_z
)
endif()
