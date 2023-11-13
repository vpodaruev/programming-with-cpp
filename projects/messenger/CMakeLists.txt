cmake_minimum_required(VERSION 3.20)

set(TARGET "messenger")

set(SOURCES
    main.cpp
)

project(${TARGET} CXX)

find_package(
    Boost 1.83.0 EXACT REQUIRED
    COMPONENTS headers
)

include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

add_executable(${TARGET} ${SOURCES})

target_link_libraries(${TARGET} ${Boost_LIBRARIES})
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(${TARGET} ws2_32)
endif()

install(TARGETS ${TARGET})
