cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra")

cmake_path(SET LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")

include_directories(
    ${LIB_DIR}
)

add_subdirectory(07/calculator)

add_subdirectory(08/vec)
add_subdirectory(08/logic_elements)

add_subdirectory(ch12/shape_primitives)
add_subdirectory(ch12/koch_snowflake)

add_subdirectory(ch13/cross_wheel)
add_subdirectory(ch13/fibonacci_spiral)
add_subdirectory(ch13/hexagon_tile)

add_subdirectory(ch14/logic_shapes)

add_subdirectory(messenger)